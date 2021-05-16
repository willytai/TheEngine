#ifndef _SERIALIZER_H__
#define _SERIALIZER_H__

#include "yaml-cpp/yaml.h"

#include "core/core.h"
#include "core/scene/scene.h"
#include "core/scene/entity.h"

namespace Engine7414 {
	class Serializer
	{
	public:
		Serializer(const Ref<Scene>& scene);
		~Serializer() = default;

		// TODO error handling!!!!
		void serialize(const char* filepath);
		void deserialize(const char* filepath);

	private:
		void serializeEntity(YAML::Emitter& out, Entity entity);

	private:
		Ref<Scene> _scene;
	};
}

#endif
