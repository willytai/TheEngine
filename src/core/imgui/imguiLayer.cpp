#include "core/util/font.h"
#include "core/app.h"
#include "core/imgui/imguiLayer.h"
#include "imgui/imgui.h"
#include "imgui/backends/imgui_impl_glfw.h"
#include "imgui/backends/imgui_impl_opengl3.h"

namespace Engine7414
{
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

    void ImGuiLayer::begin() {
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();
    }

    void ImGuiLayer::end() {

        ImGuiIO& io = ImGui::GetIO();
        io.DisplaySize = ImVec2( (float)App::getWindow()->getWidth(), (float)App::getWindow()->getHeight() );

        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData( ImGui::GetDrawData() );

        // docking stuff
        if ( io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable ) {
            GLFWwindow* backup_current_context = glfwGetCurrentContext();
            ImGui::UpdatePlatformWindows();
            ImGui::RenderPlatformWindowsDefault();
            glfwMakeContextCurrent(backup_current_context);
        }
    }

    void ImGuiLayer::onAttach() {
        IMGUI_CHECKVERSION();
        ImGui::CreateContext();

        ImGuiIO& io = ImGui::GetIO();
        io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
        io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
        io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;

        // load font
        auto loadFunc = [&](const char* filepath, float size_pixels) {
            io.Fonts->AddFontFromFileTTF( filepath, size_pixels );
        };
        FontLoader::load( loadFunc );

        ImGui::StyleColorsDark();

        // When viewports are enabled we tweak WindowRounding/WindowBg
        // so platform windows can look identical to regular ones.
        ImGuiStyle& style = ImGui::GetStyle();
        if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable) {
            style.WindowRounding = 0.0f;
            style.Colors[ImGuiCol_WindowBg].w = 1.0f;
        }

        ImGui_ImplGlfw_InitForOpenGL( (GLFWwindow*)App::getWindow()->nativeWindow(), true );
        ImGui_ImplOpenGL3_Init( "#version 410 core" );

        CORE_INFO( "ImGui Initialized" );
    }

    void ImGuiLayer::onDetach() {
        ImGui_ImplOpenGL3_Shutdown();
        ImGui_ImplGlfw_Shutdown();
        ImGui::DestroyContext();
    }

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
