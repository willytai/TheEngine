#include "core/scene/serializer.h"
#include "core/scene/components.h"

#include <fstream>

// encode/decode self-defined types
namespace YAML {
	template<>
	struct convert<glm::vec3> {
		static Node encode(const glm::vec3& rhs) {
			Node node;
			node.push_back(rhs.x);
			node.push_back(rhs.y);
			node.push_back(rhs.z);
			return node;
		}
		static bool decode(const Node& node, glm::vec3& rhs) {
			if (!node.IsSequence() || node.size() != 3) return false;
			rhs.x = node[0].as<float>();
			rhs.y = node[1].as<float>();
			rhs.z = node[2].as<float>();
			return true;
		}
	};

	template<>
	struct convert<glm::vec4> {
		static Node encode(const glm::vec4& rhs) {
			Node node;
			node.push_back(rhs.x);
			node.push_back(rhs.y);
			node.push_back(rhs.z);
			node.push_back(rhs.w);
			return node;
		}
		static bool decode(const Node& node, glm::vec4& rhs) {
			if (!node.IsSequence() || node.size() != 4) return false;
			rhs.x = node[0].as<float>();
			rhs.y = node[1].as<float>();
			rhs.z = node[2].as<float>();
			rhs.w = node[3].as<float>();
			return true;
		}
	};
}

namespace Engine7414 {
	YAML::Emitter& operator << (YAML::Emitter& out, const glm::vec3& v) {
		out << YAML::Flow;
		out << YAML::BeginSeq << v.x << v.y << v.z << YAML::EndSeq;
		return out;
	}

	YAML::Emitter& operator << (YAML::Emitter& out, const glm::vec4& v) {
		out << YAML::Flow;
		out << YAML::BeginSeq << v.x << v.y << v.z << v.w << YAML::EndSeq;
		return out;
	}

	YAML::Emitter& operator << (YAML::Emitter& out, const CameraBase::Type& type) {
		out << (int)type << YAML::Comment(type == CameraBase::Type::Orthographic ? "orthographic" : "perspective");
		return out;
	}

	Serializer::Serializer(const Ref<Scene>& scene) :
		_scene(scene)
	{}

	void Serializer::serialize(const char* filepath) {
		CORE_INFO("Saving scene: {} to {}", "<Name of the Scene>", filepath);

		YAML::Emitter out;
		out << YAML::BeginMap;
		out << YAML::Key << "Scene" << YAML::Value << "<Name of the Scene>";
		out << YAML::Key << "Entities" << YAML::Value << YAML::BeginSeq;
		_scene->_registry.each([&](auto& enttID) {
			this->serializeEntity(out, { enttID, _scene.get() });
		});
		out << YAML::EndSeq << YAML::EndMap;

		std::ofstream fout(filepath);
		fout << out.c_str();
		fout.close();
	}

	void Serializer::deserialize(const char* filepath) {
		YAML::Node data = YAML::LoadFile(filepath);

		if (!data["Scene"]) return;
		CORE_INFO("Loading scene: {}", data["Scene"].as<std::string>());

		if (data["Entities"]) {
			for (const auto& entity : data["Entities"]) {
				uint32_t id = entity["ID"].as<uint32_t>(); // TODO
				std::string name;
				auto tag = entity["TagComponent"];
				if (tag) name = tag["name"].as<std::string>();

				Entity deserializedEntity = _scene->createEntity(name.c_str());

				auto transform = entity["TransformComponent"];
				if (transform) {
					auto& comp = deserializedEntity.getOrEmplaceDefault<TransformComponent>();
					comp.translation = transform["translation"].as<glm::vec3>();
					comp.rotation = transform["rotation"].as<glm::vec3>();
					comp.scale = transform["scale"].as<glm::vec3>();
				}

				auto camera = entity["CameraComponent"];
				if (camera) {
					CameraBase::Type type = (CameraBase::Type)camera["type"].as<int>();
					auto& comp = deserializedEntity.getOrEmplaceDefault<CameraComponent>(type);
					comp.active = camera["active"].as<bool>();
					comp.camera->params.size = type == CameraBase::Type::Orthographic ? camera["parameters"]["size"].as<float>()
																				      : camera["parameters"]["fov"].as<float>();
					comp.camera->params.aspect = camera["parameters"]["aspectRatio"].as<float>();
					comp.camera->params.nearClip = camera["parameters"]["nearClip"].as<float>();
					comp.camera->params.farClip = camera["parameters"]["farClip"].as<float>();
				}

				auto sprite = entity["SpriteRendererComponent"];
				if (sprite) {
					auto& comp = deserializedEntity.getOrEmplaceDefault<SpriteRendererComponent>();
					comp.color = sprite["color"].as<glm::vec4>();
				}
			}
		}
	}

	void Serializer::serializeEntity(YAML::Emitter& out, Entity entity) {
		out << YAML::BeginMap;

		out << YAML::Key << "ID" << YAML::Value << "7414"; // TODO

		if (entity.has<TagComponent>()) {
			auto& tag = entity.get<TagComponent>();
			out << YAML::Key << "TagComponent";
			out << YAML::BeginMap;
			out << YAML::Key << "name" << YAML::Value << tag.name;
			out << YAML::EndMap;
		}

		if (entity.has<TransformComponent>()) {
			auto& transform = entity.get<TransformComponent>();
			out << YAML::Key << "TransformComponent";
			out << YAML::BeginMap;
			out << YAML::Key << "translation" << YAML::Value << transform.translation;
			out << YAML::Key << "rotation" << YAML::Value << transform.rotation;
			out << YAML::Key << "scale" << YAML::Value << transform.scale;
			out << YAML::EndMap;
		}

		if (entity.has<CameraComponent>()) {
			auto& camera = entity.get<CameraComponent>();
			out << YAML::Key << "CameraComponent";
			out << YAML::BeginMap;
			out << YAML::Key << "active" << YAML::Value << camera.active;
			out << YAML::Key << "type" << YAML::Value << camera.camera->getType();
			out << YAML::Key << "parameters";
			out << YAML::BeginMap;
			out << YAML::Key << (camera.camera->getType() == CameraBase::Type::Orthographic ? "size" : "fov") << YAML::Value << camera.camera->params.size;
			out << YAML::Key << "aspectRatio" << YAML::Value << camera.camera->params.aspect;
			out << YAML::Key << "nearClip" << YAML::Value << camera.camera->params.nearClip;
			out << YAML::Key << "farClip" << YAML::Value << camera.camera->params.farClip;
			out << YAML::EndMap;
			out << YAML::EndMap;
		}

		if (entity.has<SpriteRendererComponent>()) {
			auto& sprite = entity.get<SpriteRendererComponent>();
			out << YAML::Key << "SpriteRendererComponent";
			out << YAML::BeginMap;
			out << YAML::Key << "color" << YAML::Value << sprite.color;
			out << YAML::EndMap;
		}

		out << YAML::EndMap;
	}
}