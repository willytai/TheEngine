#include "core/app.h"
#include "core/imgui/imguiLayer.h"
#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"

namespace Engine7414
{
    ImGuiLayer::ImGuiLayer() :
        Layer("ImGuiLayer") {}

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

        ImGui::StyleColorsDark();

        ImGui_ImplGlfw_InitForOpenGL( (GLFWwindow*)App::getWindow()->nativeWindow(), true );
        ImGui_ImplOpenGL3_Init( "#version 410 core" );
    }

    void ImGuiLayer::onDetach() {
        ImGui_ImplOpenGL3_Shutdown();
        ImGui_ImplGlfw_Shutdown();
        ImGui::DestroyContext();
    }

    void ImGuiLayer::onEvent(Event& event) {
    }

    void ImGuiLayer::onImGui() {
        static bool stat;
        ImGui::ShowDemoWindow( &stat );
    }
}