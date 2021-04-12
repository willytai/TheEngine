#ifndef __EDITOR_LAYER_H__
#define __EDITOR_LAYER_H__

#include "core/layer/layer.h"
#include "imgui/imgui.h"

#include "core/core.h"
#include "core/renderer/texture.h"
#include "core/renderer/frameBuffer.h"
#include "core/renderer/cameraController.h"
#include <glm/glm.hpp>

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
        ImGuiDockNodeFlags  dockspace_flags = ImGuiDockNodeFlags_None;
        ImGuiWindowFlags    window_flags    = ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDocking;
        ImVec2              ViewportSize    = {0, 0};
        bool                dockspaceOpen   = false;
        bool                ViewportFocused = false;
        bool                ViewportHovered = false;
        bool                ViewportCollapsed = false;

        glm::vec4                        _color;
        CameraController     _cameraController;
        Ref<Engine7414::Texture2D>    _texture;
        Ref<Engine7414::Texture2D>    _texture1;
        Ref<Engine7414::FrameBuffer>  _framebuffer;
    };
}

#endif /* __EDITOR_LAYER_H__ */
