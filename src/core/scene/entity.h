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
        static Entity Null;
    public:
        Entity() = default;
        Entity(entt::entity handle, Scene* scene);

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
        const T& get() const {
            CORE_ASSERT(this->has<T>(), "entity doesn't have component");
            return _scene->_registry.get<T>(_handle);
        }

        template<typename T, typename... Args>
        T& getOrEmplaceDefault(Args&&... args) {
            if (this->has<T>()) return this->get<T>();
            else return this->emplace<T>(std::forward<Args>(args)...);
        }

        template<typename T>
        bool has() const {
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

        // remove component
        template<typename T>
        void remove() {
            _scene->_registry.remove<T>(_handle);
        }

        // deletion
        void destroy() {
            _scene->_registry.destroy(_handle);
        }

        operator bool() const { return _handle != entt::null; }

        // for ImGui (unique indexing)
        operator intptr_t() const { return (intptr_t)_handle; }

        bool operator==(const Entity& other) {
            return _handle == other._handle && _scene == other._scene;
        }

    private:
        entt::entity _handle = entt::null;
        Scene*       _scene = NULL;
    };
}

#endif
