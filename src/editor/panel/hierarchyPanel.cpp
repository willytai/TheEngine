#include "core/scene/components.h"
#include "core/renderer/renderer2D.h"
#include "core/util/drawUtil.h"
#include "editor/panel/hierarchyPanel.h"
#include <imgui/imgui.h>

namespace Engine7414
{
    HierarchyPanel::HierarchyPanel() {
        _context.reset();
        _selectedEntity = Entity::Null;
    }

    HierarchyPanel::HierarchyPanel(const Ref<Scene>& context) {
        this->setContext(context);
        _selectedEntity = Entity::Null;
    }

    void HierarchyPanel::setContext(const Ref<Scene>& context) {
        _context = context;
        _selectedEntity = Entity::Null;
    }

    void HierarchyPanel::selectEntity(const Entity& entity) {
        _selectedEntity = entity;
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

        // only popup on blank parts of the window when right button is clicked
        if (ImGui::BeginPopupContextWindow(0, ImGuiPopupFlags_MouseButtonRight | ImGuiPopupFlags_NoOpenOverItems)) {
            if (ImGui::MenuItem("create empty entity")) {
                _context->createEntity();
            }

            ImGui::EndPopup();
        }

        ImGui::End();

        // property panel
        this->onPropertyWindow();

        // delete the item
        while (_removeEntity.size()) {
            _removeEntity.front().destroy();
            if (_selectedEntity == _removeEntity.front()) {
                _selectedEntity = Entity::Null;
            }
            _removeEntity.pop();
        }
    }

    void HierarchyPanel::onPropertyWindow() {
        ImGui::Begin("Properties");
        if (_selectedEntity) {

            static char buffer[BUF_MAX];
            if (_selectedEntity.has<TagComponent>()) {
                auto& tag = _selectedEntity.get<TagComponent>();
#ifdef _MSC_VER
                strcpy_s<BUF_MAX>(buffer, tag.name.c_str());
#else
                strcpy(buffer, tag.name.c_str());
#endif
                if (ImGui::InputText("##name", buffer, BUF_MAX)) {
                    tag.name = std::string(buffer);
                }
            }

            ImGui::SameLine(ImGui::GetWindowWidth() - 105.0f - ImGui::GetTextLineHeight() / 2.0f);

            // draw all the components that can be added
            if (ImGui::Button("Add Component")) ImGui::OpenPopup("Add Component");
            if (ImGui::BeginPopup("Add Component")) {
                if (ImGui::BeginMenu("Camera")) {
                    if (ImGui::MenuItem("Perspective")) {
                        _selectedEntity.emplace<CameraComponent>(CameraBase::Type::Perspective, false, _context->aspectRatio());
                        ImGui::CloseCurrentPopup();
                    }
                    if (ImGui::MenuItem("Orthographic")) {
                        _selectedEntity.emplace<CameraComponent>(CameraBase::Type::Orthographic, false, _context->aspectRatio());
                        ImGui::CloseCurrentPopup();
                    }
                    ImGui::EndMenu();
                }

                if (ImGui::MenuItem("Sprite")) {
                    _selectedEntity.emplace<SpriteRendererComponent>();
                    ImGui::CloseCurrentPopup();
                }

                ImGui::EndPopup();
            }

            this->drawProperties(_selectedEntity);
        }
        ImGui::End();
    }

    void HierarchyPanel::drawEntity(const Entity& entity) {
        ImGuiTreeNodeFlags flags = ((_selectedEntity == entity) ? ImGuiTreeNodeFlags_Selected : 0) |
                                   ImGuiTreeNodeFlags_OpenOnArrow |
                                   ImGuiTreeNodeFlags_SpanAvailWidth;

        bool expanded = ImGui::TreeNodeEx((void*)(intptr_t)entity, flags, "%s", entity.get<TagComponent>().name.c_str() );
        if ( ImGui::IsItemClicked() ) {
            _selectedEntity = entity;
        }

        // item will be deleted after the frame is rendered
        if (ImGui::BeginPopupContextItem()) {
            if (ImGui::MenuItem("delete entity")) {
                _removeEntity.push(entity);
            }
            ImGui::EndPopup();
        }

        if ( expanded ) {
            ImGui::Text( "expanded" );
            ImGui::TreePop();
        }
    }

    template<typename ComponentType, typename UIFunction>
    void drawComponent(const char* label, Entity entity, UIFunction UIFunc, bool removable = true) {
        static ImGuiTreeNodeFlags treeNodeFlags = ImGuiTreeNodeFlags_DefaultOpen |
                                                  ImGuiTreeNodeFlags_SpanAvailWidth |
                                                  ImGuiTreeNodeFlags_SpanAvailWidth |
                                                  ImGuiTreeNodeFlags_FramePadding |
                                                  ImGuiTreeNodeFlags_Framed;
        if (entity.has<ComponentType>()) {
            auto& component = entity.get<ComponentType>();
            bool remove = false;
            ImGui::Separator();
            bool open = ImGui::TreeNodeEx(label, treeNodeFlags);
            if (removable && ImGui::BeginPopupContextItem()) {
                if (ImGui::MenuItem("remove component")) {
                    remove = true;
                }
                ImGui::EndPopup();
            }

            if (open) {
                UIFunc(component);
                ImGui::TreePop();
            }

            if (remove) entity.remove<ComponentType>();
        }
    }

    void HierarchyPanel::drawProperties(Entity& entity) {
        drawComponent<TransformComponent>("transform", entity, [](auto& transform) {
            bool valChanged = false;
            valChanged |= DrawUtil::drawVec3Control("translation", transform.translation);
            valChanged |= DrawUtil::drawVec3Control("rotation", transform.rotation);
            valChanged |= DrawUtil::drawVec3Control("scale", transform.scale, 1.0f);
            if (valChanged) Renderer2D::setUpdateMatFlag();
        }, false);

        drawComponent<CameraComponent>("camera", entity, [](auto& camera) {
            ImGui::Text("Projection: %s", camera.camera->projection_str());
            ImGui::Checkbox("Primary", &camera.active);

            if (dynamic_cast<Camera2D*>(camera.camera.get())) {
                bool& update = camera.camera->__updateProj;
                update |= ImGui::SliderFloat("size", &camera.camera->params.size, 1.0f, 10.0f);
                update |= ImGui::SliderFloat("near", &camera.camera->params.nearClip, -10.0f, -1.0f);
                update |= ImGui::SliderFloat("far",  &camera.camera->params.farClip, 1.0f, 10.0f);
            }

            if (dynamic_cast<Camera3D*>(camera.camera.get())) {
                bool& update = camera.camera->__updateProj;
                update |= ImGui::SliderFloat("fov",  &camera.camera->params.size, 30.0f, 60.0f);
                update |= ImGui::SliderFloat("near", &camera.camera->params.nearClip, 1.0f, 10.0f);
                update |= ImGui::SliderFloat("far",  &camera.camera->params.farClip, 100.0f, 1000.0f);
            }
        });

        drawComponent<SpriteRendererComponent>("sprite", entity, [](auto& sprite) {
            ImGui::ColorEdit4("color", &sprite.color.r);
        });
    }
}
