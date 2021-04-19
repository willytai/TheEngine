#include "core/scene/scene.h"
#include "core/scene/entity.h"
#include "core/scene/components.h"
#include "core/renderer/renderer2D.h"

namespace Engine7414
{
    Scene::Scene() {
    }

    Entity Scene::createEntity(const char* name) {
        // every entity should have a transform componenet and a tag component
        if (!name) name = "Entity";
        auto handle = _registry.create();
        _registry.emplace<TagComponent>(handle, name);
        _registry.emplace<TransformComponent>(handle); // identity transform
        return Entity(handle, this);
    }

    void Scene::onUpdate(const TimeStep& deltaTime, const bool& viewportFocused) {
        TransformComponent* cameraTransform = nullptr;
        CameraComponent* sceneCamera = nullptr;
        // active camera position update
        {
            // find the active camera and call the onUpdate function from its controller if viewport is focused
            auto group = _registry.group<CameraComponent>(entt::get<TransformComponent>);
            for (auto entity : group) {
                std::tuple<CameraComponent&, TransformComponent&> tup = group.get(entity);
                auto& [camera, transform] = tup;
                if (camera.active) {
                    if (viewportFocused) {
                        camera.controller.onUpdate(deltaTime, transform.translation);
                    }
                    cameraTransform = &transform;
                    sceneCamera = &camera;
                    break;
                }
            }
        }

        // start renderering
        if (sceneCamera)
        {
            Renderer2D::beginScene(*cameraTransform, (*sceneCamera).camera.get());
            auto group = _registry.group<SpriteRendererComponent>(entt::get<TransformComponent>);
            for (auto entity : group) {
                const auto& [sprite, transform] = group.get(entity);
                Renderer2D::drawQuad(transform.transform(), sprite.color);
            }
            Renderer2D::endScene();
        }
    }

    void Scene::onResize(const float& width, const float& height) {
        // find the active camera and resize
        // TODO: if its a camera without a controller, it would not be able to resize
        //       which might be desirable but also might not, fix in the future
        auto view = _registry.view<CameraComponent>();
        for (auto entity : view) {
            auto& camera = view.get<CameraComponent>(entity);
            if (camera.active) {
                camera.controller.onResize(width, height);
            }
        }
    }

    void Scene::onEvent(Event& event) {
        auto view = _registry.view<CameraComponent>();
        for (auto entity : view) {
            auto& camera = view.get<CameraComponent>(entity);
            if (camera.active) {
                camera.controller.onEvent(event);
            }
        }
    }
}
