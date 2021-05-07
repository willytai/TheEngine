#include "core/scene/components.h"
#include "editor/panel/hierarchyPanel.h"
#include <imgui/imgui.h>

#include "core/renderer/renderer2D.h"

namespace Engine7414
{
    HierarchyPanel::HierarchyPanel() {
        _context.reset();
        _selectedEntity = Entity{ entt::null, NULL };
    }

    HierarchyPanel::HierarchyPanel(const Ref<Scene>& context) {
        this->setContext(context);
        _selectedEntity = Entity{ entt::null, NULL };
    }

    void HierarchyPanel::setContext(const Ref<Scene>& context) {
        _context = context;
    }

    void HierarchyPanel::onImGui() {
        CORE_ASSERT( _context, "context not set for hierarchy panel" );
        ImGui::Begin("Scene Hierarchy");
        _context->_registry.each(
            [&](auto entityID){
                this->drawEntity({ entityID, _context.get() });
            }
        );

        // deselection
        if (ImGui::IsMouseClicked(ImGuiMouseButton_Left) && ImGui::IsWindowHovered()) {
            _selectedEntity = Entity::Null;
        }

        ImGui::End();
    
        ImGui::Begin("Properties");
        if (_selectedEntity) {
            this->drawProperties(_selectedEntity);
        }
        ImGui::End();
    }

    void HierarchyPanel::drawEntity(const Entity& entity) {
        ImGuiTreeNodeFlags flags = ((_selectedEntity == entity) ? ImGuiTreeNodeFlags_Selected : 0) |
                                   ImGuiTreeNodeFlags_OpenOnArrow;
        bool expanded = ImGui::TreeNodeEx((void*)(intptr_t)entity, flags, "%s", entity.get<TagComponent>().name.c_str() );
        if ( ImGui::IsItemClicked() ) {
            _selectedEntity = entity;
        }
        if ( expanded ) {
            ImGui::Text( "expanded" );
            ImGui::TreePop();
        }
    }

    static char buffer[BUF_MAX];
    void HierarchyPanel::drawProperties(Entity& entity) {
        if (entity.has<TagComponent>()) {
            auto& tag = entity.get<TagComponent>();
#ifdef _MSC_VER
            strcpy_s<BUF_MAX>(buffer, tag.name.c_str());
#else
            strcpy(buffer, tag.name.c_str());
#endif
            if (ImGui::InputText("Name", buffer, BUF_MAX)) {
                tag.name = std::string(buffer);
            }
        }

        if (entity.has<TransformComponent>()) {
            auto& transform = entity.get<TransformComponent>();
            if (ImGui::TreeNodeEx("transform", ImGuiTreeNodeFlags_DefaultOpen)) {
                if (ImGui::DragFloat3("", &transform.translation.x, 0.5f, -10.0f, 10.0f)) {
                    Renderer2D::setUpdateMatFlag();
                }
                ImGui::TreePop();
            }
        }

        if (entity.has<CameraComponent>()) {
            auto& camera = entity.get<CameraComponent>();
            if (ImGui::TreeNodeEx("camera", ImGuiTreeNodeFlags_DefaultOpen)) {
                ImGui::Text("Projection: %s", camera.camera->projection_str());

                if (dynamic_cast<Camera2D*>(camera.camera.get())) {
                    bool& update = camera.camera->__updateProj;
                    update |= ImGui::SliderFloat("size",   &camera.camera->params.size, 1.0f, 10.0f);
                    update |= ImGui::SliderFloat("near",   &camera.camera->params.nearClip, -10.0f, -1.0f);
                    update |= ImGui::SliderFloat("far",    &camera.camera->params.farClip, 1.0f, 10.0f );
                }

                if (dynamic_cast<Camera3D*>(camera.camera.get())) {
                    bool& update = camera.camera->__updateProj;
                    update |= ImGui::SliderFloat("fov",  &camera.camera->params.size, 30.0f, 60.0f);
                    update |= ImGui::SliderFloat("near", &camera.camera->params.nearClip, 1.0f, 10.0f);
                    update |= ImGui::SliderFloat("far",  &camera.camera->params.farClip, 100.0f, 1000.0f);
                }

                ImGui::TreePop();
            }
        }

        if (entity.has<SpriteRendererComponent>()) {
            auto& sprite = entity.get<SpriteRendererComponent>();
            if (ImGui::TreeNodeEx("sprite", ImGuiTreeNodeFlags_DefaultOpen)) {
                ImGui::ColorEdit4("color", &sprite.color.r);

                ImGui::TreePop();
            }
        }
    }
}
