#include "core/util/font.h"
#include "core/app.h"
#include "core/imgui/imguiLayer.h"

// for * operator to work on ImVec4
#ifndef IMGUI_DEFINE_MATH_OPERATORS
#define IMGUI_DEFINE_MATH_OPERATORS
#endif

#include <imgui/imgui.h>
#include <imgui/imgui_internal.h>
#include <imgui/backends/imgui_impl_glfw.h>
#include <imgui/backends/imgui_impl_opengl3.h>

#undef IMGUI_DEFINE_MATH_OPERATORS

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
        auto loadFunc = [&](const char* filepath, float size_pixels, FontLoader::Type type) {
            auto ret = io.Fonts->AddFontFromFileTTF( filepath, size_pixels );
            switch (type) {
                case FontLoader::Type::DEFAULT_BOLD: boldFont = ret; break;
                case FontLoader::Type::DEFAULT_ITALIC: italicFont = ret; break;
                case FontLoader::Type::DEFAULT_DEFAULT: io.FontDefault = ret; break;
            }
        };
        FontLoader::load( loadFunc );

        this->initStyle();

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
        boldFont = NULL;
        italicFont = NULL;
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

    void ImGuiLayer::initStyle() {
        // ImGui::StyleColorsDark();
        ImVec4* colors = ImGui::GetStyle().Colors;
        colors[ImGuiCol_WindowBg] = ImVec4(0.1f, 0.1f, 0.1f, 1.0f);
        colors[ImGuiCol_MenuBarBg] = ImVec4(0.14f, 0.14f, 0.14f, 1.00f);
        colors[ImGuiCol_ChildBg] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
        colors[ImGuiCol_PopupBg] = colors[ImGuiCol_WindowBg] + ImVec4(0.05f, 0.05f, 0.05f, 0.00f);
        colors[ImGuiCol_Border] = ImVec4(0.43f, 0.43f, 0.50f, 0.50f);
        colors[ImGuiCol_BorderShadow] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);

        // does't really need to be changed
        colors[ImGuiCol_Text] = ImVec4(1.00f, 1.00f, 1.00f, 1.00f);
        colors[ImGuiCol_TextDisabled] = ImVec4(0.50f, 0.50f, 0.50f, 1.00f);

        // titile bar
        colors[ImGuiCol_TitleBg] = colors[ImGuiCol_WindowBg] + ImVec4(0.05f, 0.05f, 0.05f, 0.0f);
        colors[ImGuiCol_TitleBgActive] = colors[ImGuiCol_TitleBg];
        colors[ImGuiCol_TitleBgCollapsed] = colors[ImGuiCol_TitleBg] * ImVec4(1.0f, 1.0f, 1.0f, 0.5f);

        // tab
        colors[ImGuiCol_Tab] = colors[ImGuiCol_TitleBg] + ImVec4(0.05f, 0.05f, 0.05f, 0.0f);
        colors[ImGuiCol_TabHovered] = colors[ImGuiCol_Tab] + ImVec4(0.05f, 0.05f, 0.05f, 0.0f);
        colors[ImGuiCol_TabActive] = colors[ImGuiCol_Tab] + ImVec4(0.15f, 0.15f, 0.15f, 0.0f);
        colors[ImGuiCol_TabUnfocused] = colors[ImGuiCol_Tab];
        colors[ImGuiCol_TabUnfocusedActive] = colors[ImGuiCol_TabActive] - ImVec4(0.02f, 0.02f, 0.02f, 0.0f);

        // header
        colors[ImGuiCol_Header] = colors[ImGuiCol_PopupBg] + ImVec4(0.1f, 0.1f, 0.1f, 0.0f);
        colors[ImGuiCol_HeaderHovered] = colors[ImGuiCol_Header] + ImVec4(0.1f, 0.1f, 0.1f, 0.0f);
        colors[ImGuiCol_HeaderActive] = colors[ImGuiCol_Header] + ImVec4(0.05f, 0.05f, 0.05f, 0.0f);

        // frame
        colors[ImGuiCol_FrameBg] = colors[ImGuiCol_Header];
        colors[ImGuiCol_FrameBgHovered] = colors[ImGuiCol_HeaderHovered];
        colors[ImGuiCol_FrameBgActive] = colors[ImGuiCol_HeaderActive];

        // button
        colors[ImGuiCol_Button] = colors[ImGuiCol_FrameBg];
        colors[ImGuiCol_ButtonHovered] = colors[ImGuiCol_FrameBgHovered];
        colors[ImGuiCol_ButtonActive] = colors[ImGuiCol_FrameBgActive];

        // seperator
        colors[ImGuiCol_Separator] = colors[ImGuiCol_Border];
        colors[ImGuiCol_SeparatorHovered] = colors[ImGuiCol_HeaderHovered];
        colors[ImGuiCol_SeparatorActive] = colors[ImGuiCol_SeparatorHovered] + ImVec4(0.2f, 0.2f, 0.2f, 0.0f);

        // slider
        colors[ImGuiCol_SliderGrab] = ImVec4(0.60f, 0.70f, 0.878f, 1.00f);
        colors[ImGuiCol_SliderGrabActive] = ImVec4(0.75f, 0.80f, 0.88f, 1.00f);

        colors[ImGuiCol_ScrollbarBg] = colors[ImGuiCol_WindowBg];
        colors[ImGuiCol_ScrollbarGrab] = ImVec4(0.31f, 0.31f, 0.31f, 1.00f);
        colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(0.41f, 0.41f, 0.41f, 1.00f);
        colors[ImGuiCol_ScrollbarGrabActive] = ImVec4(0.51f, 0.51f, 0.51f, 1.00f);
        colors[ImGuiCol_CheckMark] = ImVec4(0.26f, 0.59f, 0.98f, 1.00f);
        colors[ImGuiCol_ResizeGrip] = ImVec4(0.26f, 0.59f, 0.98f, 0.20f);
        colors[ImGuiCol_ResizeGripHovered] = ImVec4(0.26f, 0.59f, 0.98f, 0.67f);
        colors[ImGuiCol_ResizeGripActive] = ImVec4(0.26f, 0.59f, 0.98f, 0.95f);
        colors[ImGuiCol_DockingPreview] = colors[ImGuiCol_HeaderActive] * ImVec4(1.0f, 1.0f, 1.0f, 0.7f);
        colors[ImGuiCol_DockingEmptyBg] = ImVec4(0.20f, 0.20f, 0.20f, 1.00f);
        colors[ImGuiCol_PlotLines] = ImVec4(0.61f, 0.61f, 0.61f, 1.00f);
        colors[ImGuiCol_PlotLinesHovered] = ImVec4(1.00f, 0.43f, 0.35f, 1.00f);
        colors[ImGuiCol_PlotHistogram] = ImVec4(0.90f, 0.70f, 0.00f, 1.00f);
        colors[ImGuiCol_PlotHistogramHovered] = ImVec4(1.00f, 0.60f, 0.00f, 1.00f);
        colors[ImGuiCol_TableHeaderBg] = ImVec4(0.19f, 0.19f, 0.20f, 1.00f);
        colors[ImGuiCol_TableBorderStrong] = ImVec4(0.31f, 0.31f, 0.35f, 1.00f);   // Prefer using Alpha=1.0 here
        colors[ImGuiCol_TableBorderLight] = ImVec4(0.23f, 0.23f, 0.25f, 1.00f);   // Prefer using Alpha=1.0 here
        colors[ImGuiCol_TableRowBg] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
        colors[ImGuiCol_TableRowBgAlt] = ImVec4(1.00f, 1.00f, 1.00f, 0.06f);
        colors[ImGuiCol_TextSelectedBg] = ImVec4(0.26f, 0.59f, 0.98f, 0.35f);
        colors[ImGuiCol_DragDropTarget] = ImVec4(1.00f, 1.00f, 0.00f, 0.90f);
        colors[ImGuiCol_NavHighlight] = ImVec4(0.26f, 0.59f, 0.98f, 1.00f);
        colors[ImGuiCol_NavWindowingHighlight] = ImVec4(1.00f, 1.00f, 1.00f, 0.70f);
        colors[ImGuiCol_NavWindowingDimBg] = ImVec4(0.80f, 0.80f, 0.80f, 0.20f);
        colors[ImGuiCol_ModalWindowDimBg] = ImVec4(0.80f, 0.80f, 0.80f, 0.35f);
    }
}
