#include "core/scene/scene.h"
#include "core/scene/components.h"
#include "core/renderer/renderer2D.h"

namespace Engine7414
{
    Scene::Scene() {
    }

    void Scene::onUpdate(const TimeStep& deltaTime) {
        auto group = _registry.group<TransformComponent>(entt::get<SpriteRendererComponent>);
        for (auto entity : group) {
            const auto& [transform, sprite] = group.get<TransformComponent, SpriteRendererComponent>(entity);
            Renderer2D::drawQuad( transform.transform(), sprite.color );
        }
    }
}
