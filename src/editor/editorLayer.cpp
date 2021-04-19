#include "core/app.h"
#include "core/renderer/renderer2D.h"
#include "editor/editorLayer.h"
#include "imgui/imgui.h"

namespace Engine7414
{
    EditorLayer::EditorLayer(const char* name) :
        Layer(name)
    {

    }

    EditorLayer::~EditorLayer() {

    }

    void EditorLayer::onAttach() {
        // ImGui checks
        ImGuiIO& io = ImGui::GetIO();
        CORE_VERIFY( io.ConfigFlags & ImGuiConfigFlags_DockingEnable, "ImGui docking not enabled!" );
        dockspaceOpen = true;

        // We are using the ImGuiWindowFlags_NoDocking flag to make the parent window not dockable into,
        // because it would be confusing to have two docking targets within each others.
        window_flags |= ImGuiWindowFlags_NoTitleBar |
                        ImGuiWindowFlags_NoCollapse |
                        ImGuiWindowFlags_NoResize   |
                        ImGuiWindowFlags_NoMove     |
                        ImGuiWindowFlags_NoNavFocus |
                        ImGuiWindowFlags_NoBringToFrontOnFocus;

        // When using ImGuiDockNodeFlags_PassthruCentralNode, DockSpace() will render our background
        // and handle the pass-thru hole, so we ask Begin() to not render a background.
        if (dockspace_flags & ImGuiDockNodeFlags_PassthruCentralNode)
            window_flags |= ImGuiWindowFlags_NoBackground;


#ifdef __APPLE__
        _texture = Texture2D::create("./resource/texture/instagram.png");
        _texture1 = Texture2D::create("./resource/texture/logo.png");
#else
        _texture = Texture2D::create("C:\\Users\\Willy\\Desktop\\TheEngine\\TheEngine\\resource\\texture\\instagram.png");
        _texture1 = Texture2D::create("C:\\Users\\Willy\\Desktop\\TheEngine\\TheEngine\\resource\\texture\\logo.png");
#endif

        FrameBufferSpec spec = { 1280, 960 };
        _framebuffer = FrameBuffer::create( spec );

        // make sure the ViewportSize of the first frame is valid (not (0, 0))
        // this is going to be corrected after the first frame is rendered
        ViewportSize = { (float)spec.width, (float)spec.height };

        // scene
        _activeScene = CreateRef<Scene>();

        // test entity
        _testEntity = _activeScene->createEntity("ColoredSquare");
        _testEntity.emplace<SpriteRendererComponent>();

        // camera
        _cameraEntity = _activeScene->createEntity("Scene Camera");
        float aspect = 1280.0f / 960.0f;
        bool active = true, controllable = true;
        auto& cameraComponent = _cameraEntity.emplace<CameraComponent>(aspect, CameraBase::Orthographic, active, controllable);

        // _cameraController.createCamera2D(1280.0f / 960.0f);

        CORE_INFO( "Editor Layer Initialized" );
    }

    void EditorLayer::onDetach() {
        dockspaceOpen = false;
        window_flags = ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDocking;
        dockspace_flags = ImGuiDockNodeFlags_None;
    }

    void EditorLayer::onUpdate(const TimeStep& deltaTime) {
        if ( ViewportCollapsed ) {
            // not really necesary (just to make sure the statistics are reset)
            Renderer2D::resetStat();
            return;
        }

        // update frame buffer if necessary
        const auto& fbspec = _framebuffer->spec();
        if ( (uint32_t)ViewportSize.x != fbspec.width || (uint32_t)ViewportSize.y != fbspec.height ) {
            _framebuffer->resize( (uint32_t)ViewportSize.x, (uint32_t)ViewportSize.y );
            _activeScene->onResize(ViewportSize.x, ViewportSize.y);
        }

        _framebuffer->bind();
        _activeScene->onUpdate( deltaTime, ViewportFocused );
        // Renderer2D::drawQuad({ 1.0f, 0.0f, 0.1f }, { 0.3f, 0.3f }, _texture);
        // Renderer2D::drawQuad({ -1.0f, 0.0f }, { 1.0f, 1.0f }, _texture1);
        // Renderer2D::drawQuad({ 1.0f, 0.0f }, { 0.5f, 1.0f }, _color);
        _framebuffer->unbind();
    }

    void EditorLayer::onImGui() {
        // Important: note that we proceed even if Begin() returns false (aka window is collapsed).
        // This is because we want to keep our DockSpace() active. If a DockSpace() is inactive,
        // all active windows docked into it will lose their parent and become undocked.
        // We cannot preserve the docking relationship between an active window and an inactive docking, otherwise
        // any change of dockspace/settings would lead to windows being stuck in limbo and never being visible.
        // Info: set to zero padding and window style
        const ImGuiViewport* viewport = ImGui::GetMainViewport();
        ImGui::SetNextWindowPos(viewport->WorkPos);
        ImGui::SetNextWindowSize(viewport->WorkSize);
        ImGui::SetNextWindowViewport(viewport->ID);
        ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
        ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
        ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
        ImGui::Begin("DockSpace Window", &dockspaceOpen, window_flags);
        ImGui::PopStyleVar(3);

        // DockSpace
        ImGuiID dockspace_id = ImGui::GetID("DockSpace");
        ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f), dockspace_flags);

        if (ImGui::BeginMenuBar())
        {
            if (ImGui::BeginMenu("File"))
            {
                // Disabling fullscreen would allow the window to be moved to the front of other windows,
                // which we can't undo at the moment without finer window depth/z control.
                if (ImGui::MenuItem("Exit")) App::close();

                ImGui::EndMenu();
            }
            ImGui::EndMenuBar();
        }

        // test window
        {
            auto stat = Engine7414::Renderer2D::stat();
            ImGui::Begin("Test");
            ImGui::Text( "framerate: %.0f", ImGui::GetIO().Framerate );
            ImGui::Text( "drawCalls: %d", stat.drawCalls );
            ImGui::Text( "quadCount: %d", stat.quadCount );
            ImGui::Separator();
            ImGui::Text("Entities");
            if (_testEntity) {
                ImGui::Separator();
                ImGui::Text("%s", _testEntity.get<TagComponent>());
                ImGui::ColorEdit4("color", &_testEntity.get<SpriteRendererComponent>().color[0]);
                ImGui::Separator();
            }
            ImGui::Separator();
            ImGui::End();
        }

        // Viewport Window
        {
            // Info: set to zero padding on viewport window
            ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
            ImGui::Begin("View Port");
            ImGui::PopStyleVar();

            ViewportSize      = ImGui::GetContentRegionAvail();
            ViewportFocused   = ImGui::IsWindowFocused();
            ViewportHovered   = ImGui::IsWindowHovered();
            ViewportCollapsed = ImGui::IsWindowCollapsed();

            // events should be propagated only when the viewport is focused and hovered!
            if ( ViewportFocused && ViewportHovered ) ImGuiLayer::setNoBlockEvent();
            else                                      ImGuiLayer::setBlockEvent();

            ImGui::Image( (void*)(intptr_t)_framebuffer->colorAttachmentID(),
                          ViewportSize, ImVec2(0, 1), ImVec2(1, 0) );

            ImGui::End();
        }

        // end dockspace
        ImGui::End();
    }

    void EditorLayer::onEvent(Event& event) {
        _activeScene->onEvent(event);
    }
}
