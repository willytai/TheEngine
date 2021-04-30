#include "core/util/font.h"
#include "core/imgui/GLimguiLayer.h"
#include "core/application/app.h"
#include "imgui/imgui.h"
#include "imgui/backends/imgui_impl_glfw.h"
#include "imgui/backends/imgui_impl_opengl3.h"

namespace Engine7414
{
    GLImGuiLayer::GLImGuiLayer() {

    }

    GLImGuiLayer::~GLImGuiLayer() {

    }

   void GLImGuiLayer::begin() {
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();
   }

   void GLImGuiLayer::end() {

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

   void GLImGuiLayer::onAttach() {
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

   void GLImGuiLayer::onDetach() {
        ImGui_ImplOpenGL3_Shutdown();
        ImGui_ImplGlfw_Shutdown();
        ImGui::DestroyContext();
   }
}
