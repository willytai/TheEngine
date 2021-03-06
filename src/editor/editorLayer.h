#ifndef __EDITOR_LAYER_H__
#define __EDITOR_LAYER_H__

#include "core/layer/layer.h"
#include "core/core.h"
#include "core/renderer/texture.h"
#include "core/renderer/frameBuffer.h"
#include "core/renderer/cameraController.h"
#include "core/scene/entity.h"
#include "core/scene/scene.h"
#include "core/scene/entity.h"
#include "core/scene/components.h"
#include "editor/panel/hierarchyPanel.h"
#include "editor/panel/fileExplorerPanel.h"
#include "editor/editorCamera.h"
#include "core/imgui/imguiClassExtension.h"

#include <glm/glm.hpp>
#include <imgui/imgui.h>
#include <imgui/imgui_internal.h>
#include <ImGuizmo/ImGuizmo.h>

namespace Engine7414
{
    class EditorLayer : public Layer
    {
    public:
        EditorLayer(const char* name = "Editor Layer");
        ~EditorLayer();

        void onAttach() override;
        void onDetach() override;
        void onUpdate(const TimeStep& deltaTime) override;
        void onImGui() override;
        void onEvent(Event& event) override;

    private:
        bool onKeyPressed(KeyPressedEvent& event);
        bool onMouseButtonPressed(MouseButtonPressedEvent& event);

    private:
        void newScene();
        void saveScene();
        void saveNewScene();
        void loadScene();

    private:
        // ImGui Stuffs
        ImGuiDockNodeFlags  dockspace_flags = ImGuiDockNodeFlags_None;
        ImGuiWindowFlags    window_flags    = ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDocking;
        ImVec2              ViewportSize    = { 0, 0 };
        bool                ViewportFocused = false;
        bool                ViewportHovered = false;
        bool                dockspaceOpen   = false;

        bool                _editorCameraActive = false;

        glm::vec2           _viewportMousePos = { -1.0f, -1.0f };
        ImGuizmo::OPERATION _gizmoOP = (ImGuizmo::OPERATION)0;
        Ref<EditorCamera>   _editorCamera;
        Ref<FrameBuffer>    _framebuffer;
        Ref<Scene>          _activeScene;
        HierarchyPanel      _hierarchyPanel;

        Entity              _hoveredEntity = Entity::Null;
    
        FileExplorerPanel   _fileExplorerPanel;
    };
}

#endif /* __EDITOR_LAYER_H__ */
