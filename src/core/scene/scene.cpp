#include "core/scene/scene.h"
#include "core/scene/entity.h"
#include "core/scene/components.h"
#include "core/renderer/renderer2D.h"

namespace Engine7414
{
    Entity Scene::createEntity(const char* name) {
        // every entity should have a transform componenet and a tag component
        if (!name) name = "Entity";
        auto handle = _registry.create();
        _registry.emplace<TagComponent>(handle, name);
        _registry.emplace<TransformComponent>(handle); // identity transform
        return Entity(handle, this);
    }

    void Scene::onUpdate(const TimeStep& deltaTime) {
        auto group = _registry.group<TransformComponent>(entt::get<SpriteRendererComponent>);
        for (auto entity : group) {
            const auto& [transform, sprite] = group.get<TransformComponent, SpriteRendererComponent>(entity);
            Renderer2D::drawQuad( transform.transform(), sprite.color );
        }
    }
}
