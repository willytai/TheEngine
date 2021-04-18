#ifndef __ENTITY_H__
#define __ENTITY_H__

#include "core/scene/scene.h"
#include "core/core.h"

#include <functional>

namespace Engine7414
{
	class Entity
	{
	public:
		Entity() = default;
		Entity(entt::entity handle, Scene* scene);

		operator bool() const {
			return _handle != entt::null;
		}

		template<typename T, typename... Args>
		T& emplace(Args&&... args) {
			CORE_ASSERT(!this->has<T>(), "entity already has component");
			return _scene->_registry.emplace<T>(_handle, std::forward<Args>(args)...);
		}

		template<typename T>
		T& get() {
			CORE_ASSERT(this->has<T>(), "entity doesn't have component");
			return _scene->_registry.get<T>(_handle);
		}

		template<typename T>
		bool has() {
			return _scene->_registry.all_of<T>(_handle);
		}

		// in-place
		template<typename T>
		T& patch(std::function<void(T&)> patchFn) {
			CORE_ASSERT(this->has<T>(), "entity doesn't have component");
			return _scene->_registry.patch<T>(_handle, patchFn);
		}

		// discard the old one and constructs a new one
		template<typename T, typename... Args>
		T& replace(Args&&... args) {
			CORE_ASSERT(this->has<T>(), "entity doesn't have component");
			return _scene->_registry.replace<T>(_handle, std::forward<Args>(args)...);
		}

	private:
		entt::entity _handle = entt::null;
		Scene*       _scene = NULL;
	};
}

#endif