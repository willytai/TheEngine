#include "core/scene/components.h"
#include "core/panel/hierarchyPanel.h"
#include <imgui/imgui.h>

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
        ImGui::End();
    }

    void HierarchyPanel::drawEntity(const Entity& entity) {
        ImGuiTreeNodeFlags flags = ((_selectedEntity == entity) ? ImGuiTreeNodeFlags_Selected : 0) |
                                   ImGuiTreeNodeFlags_OpenOnArrow;
        bool expanded = ImGui::TreeNodeEx((void*)(intptr_t)entity, flags, "%s", entity.get<TagComponent>().name );
        if ( ImGui::IsItemClicked() ) {
            _selectedEntity = entity;
        }
        if ( expanded ) {
            ImGui::Text( "expanded" );
            ImGui::TreePop();
        }
    }
}
