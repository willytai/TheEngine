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
            strcpy_s<BUF_MAX>(buffer, tag.name.c_str());
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
    }
}
