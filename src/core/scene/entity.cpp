#include "core/scene/entity.h"

namespace Engine7414
{
    Entity::Entity(entt::entity handle, Scene* scene) :
        _handle(handle),
        _scene(scene)
    {}
}
