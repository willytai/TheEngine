#include "core/scene/scene.h"
#include "core/scene/entity.h"
#include "core/scene/components.h"
#include "core/renderer/renderer.h"
#include "core/renderer/renderer2D.h"

namespace Engine7414
{
    Scene::Scene() {
        // default directinal light
        auto handle = _registry.create();
        _registry.emplace<TagComponent>(handle, "Directional Light");
        _registry.emplace<DirectionalLightComponent>(handle);
        _directionalLightEntity = handle;
    }

    Scene::~Scene() {
    }

    Ref<Scene> Scene::create() {
        return CreateRef<Scene>();
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
        _registry.view<NativeScriptComponent>().each(
            [&](auto entity, auto& script){
                if ( !script.instance ) {
                    script.constructFn(script.instance);
                    // TODO this should be automatically set, otherwise it's easy to mess up
                    script.instance->_entity = Entity{ entity, this };
                    script.instance->onConstruct();
                }
                script.instance->onUpdate( deltaTime );
            }
        );

        TransformComponent* cameraTransform = nullptr;
        CameraComponent* sceneCamera = nullptr;
        // active camera position update
        {
            // find the active camera and call the onUpdate function from its controller if viewport is focused
            auto group = _registry.group<CameraComponent>(entt::get<TransformComponent>);
            for (auto entity : group) {
                auto [camera, transform] = group.get(entity);
                if (camera.active) {
                    // if (viewportFocused) {
                    //     camera.controller.onUpdate(deltaTime, transform.translation);
                    // }
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
            _registry.group<SpriteRendererComponent>(entt::get<TransformComponent>).each(
                [](auto entity, auto& sprite, auto& transform) {
                    Renderer2D::drawQuad(transform.transform(), sprite.color);
                }
            );
            Renderer2D::endScene();
        }
        else {
            RenderCommands::clear();
            Renderer2D::resetStat();
        }
    }

    // make sure the framebuffer is bound before passing into this function
    void Scene::onUpdateEditor(const TimeStep& deltaTime, Ref<EditorCamera>& camera, const Ref<FrameBuffer>& currentFrameBuffer) {
        // start renderering
        if (camera)
        {
            Renderer::beginScene(this, camera, currentFrameBuffer);
            // Renderer2D::beginScene(camera, currentFrameBuffer);
            _registry.group<SpriteRendererComponent>(entt::get<TransformComponent>).each(
                [](auto entity, auto& sprite, auto& transform) {
                    Renderer::drawCube(transform.transform(), sprite.color, (int)entity);
                    // Renderer2D::drawQuad(transform.transform(), sprite.color, (int)entity);
                }
            );
            Renderer::endScene();
            // Renderer2D::endScene();
        }
    }

    void Scene::onResize(const float& width, const float& height) {
        // find the active camera and resize
        auto view = _registry.view<CameraComponent>();
        for (auto entity : view) {
            auto& camera = view.get<CameraComponent>(entity);
            camera.camera->setAspectRatio(width/height);
        }
        _sceneWidth = width;
        _sceneHeight = height;
    }

    void Scene::onEvent(Event& event) {
        // controller is removed
        auto view = _registry.view<CameraComponent>();
        for (auto entity : view) {
            auto& camera = view.get<CameraComponent>(entity);
            if (camera.active) {
                // camera.controller.onEvent(event);
            }
        }
    }

    Entity Scene::getActiveCameraEntity() {
        auto view = _registry.view<CameraComponent>();
        for (auto entity : view) {
            auto& camera = view.get<CameraComponent>(entity);
            if (camera.active) {
                return Entity( entity, this );
            }
        }
    }

    Entity Scene::getDirectionalLightEntity() {
        return { _directionalLightEntity, this };
    }
}
