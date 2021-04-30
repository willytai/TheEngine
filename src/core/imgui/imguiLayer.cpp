#include "core/imgui/imguiLayer.h"
#include "core/imgui/GLimguiLayer.h"
#include "core/imgui/MTLimguiLayer.h"
#include "core/core.h"
#include "imgui/imgui.h"

namespace Engine7414
{
    ImGuiLayer* ImGuiLayer::create(const RendererBackend& backend) {
        switch (backend) {
            case RendererBackend::OpenGL: return new GLImGuiLayer;
            case RendererBackend::Metal: return new MTLImGuiLayer;
            default: CORE_ASSERT( false, "Unsupported Backend" );
        }
        return NULL;
    }

    bool                 ImGuiLayer::__blockEvents__ = true;
    ImGuiLayer*          ImGuiLayer::__instance__ = NULL;

    ImGuiLayer::ImGuiLayer() :
        Layer("ImGuiLayer")
    {
        // make sure that there are only ONE ImGuiLayer
        if ( __instance__ ) {
            CORE_ASSERT( false, "you have already initialized the ImGuiLayer!" );
        }
        else {
            __instance__ = this;
        }
    }

    ImGuiLayer::~ImGuiLayer() {}

    void ImGuiLayer::onEvent(Event& event) {
        if ( __blockEvents__ ) {
            this->onKeyEvents( event );
            this->onMouseEvents( event );
        }
    }

    // events will be blocked if ImGui is listening
    void ImGuiLayer::onKeyEvents(Event& event) {
        EventDispatcher dispatcher( event );
        dispatcher.dispatch<KeyPressedEvent>({
            [](KeyPressedEvent& event) {
                return ImGui::GetIO().WantCaptureKeyboard;
            }
        });
        dispatcher.dispatch<KeyReleasedEvent>({
            [](KeyReleasedEvent& event) {
                return ImGui::GetIO().WantCaptureKeyboard;
            }
        });
    }

    void ImGuiLayer::onMouseEvents(Event& event) {
        EventDispatcher dispatcher( event );
        dispatcher.dispatch<MouseMovedEvent>({
            [](MouseMovedEvent& event) {
                return ImGui::GetIO().WantCaptureMouse;
            }
        });
        dispatcher.dispatch<MouseScrolledEvent>({
            [](MouseScrolledEvent& event) {
                return ImGui::GetIO().WantCaptureMouse;
            }
        });
        dispatcher.dispatch<MouseButtonPressedEvent>({
            [](MouseButtonPressedEvent& event) {
                return ImGui::GetIO().WantCaptureMouse;
            }
        });
        dispatcher.dispatch<MouseButtonReleasedEvent>({
            [](MouseButtonReleasedEvent& event) {
                return ImGui::GetIO().WantCaptureMouse;
            }
        });
    }

    void ImGuiLayer::fontZoomIn() {
        ImGui::GetIO().FontGlobalScale += 0.1f;
    }

    void ImGuiLayer::fontZoomOut() {
        ImGui::GetIO().FontGlobalScale -= 0.1f;
    }
}
