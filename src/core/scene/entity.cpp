#include "core/scene/entity.h"

namespace Engine7414
{
    Entity Entity::Null{(entt::entity)entt::null, nullptr};

    Entity::Entity(entt::entity handle, Scene* scene) :
        _handle(handle),
        _scene(scene)
    {}

    Entity::Entity(const int& entityID, Scene* scene) :
        _handle((entt::entity)entityID),
        _scene(scene)
    {}
}
