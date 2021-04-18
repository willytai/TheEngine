#ifndef __SCENE_H__
#define __SCENE_H__

#include "core/util/timeStep.h"

#if defined(__clang__)
    #pragma clang diagnostic push
    #pragma clang diagnostic ignored "-Wsign-conversion"
#elif defined(__GNUC__)
    #pragma GCC diagnostic push
    #pragma GCC diagnostic ignored "-Wsign-conversion"
#elif defined(_MSC_VER)
    #pragma warning(push)
    #pragma warning(disable : 4819)
#else
    #error "Compiler Not Supported!"
#endif

#include <entt/entt.hpp>

#if defined(__clang__)
    #pragma clang diagnostic pop
#elif defined(__GNUC__)
    #pragma GCC diagnostic pop
#elif defined(_MSC_VER)
    #pragma warning(pop)
#else
    #error "Compiler Not Supported!"
#endif

namespace Engine7414
{
    class Entity;
    class Scene
    {
        friend class Entity;
    public:
        Scene() = default;
        ~Scene() = default;

        // API
        Entity createEntity(const char* name = NULL);

        void onUpdate(const TimeStep& deltaTime);

    private:
        entt::registry _registry;
    };
}

#endif /* __SCENE_H__ */
