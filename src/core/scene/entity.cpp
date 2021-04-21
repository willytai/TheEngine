#include "core/scene/entity.h"

namespace Engine7414
{
    Entity Entity::Null{entt::null, nullptr};

    Entity::Entity(entt::entity handle, Scene* scene) :
        _handle(handle),
        _scene(scene)
    {}
}
