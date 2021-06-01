#include "core/app.h"
#include "core/renderer/renderer2D.h"
#include "core/script/scriptable.h"
#include "core/input/input.h"
#include "core/scene/serializer.h"
#include "core/util/fileDialog.h"
#include "core/math/matrixMath.h"
#include "editor/editorLayer.h"
#include <imgui/imgui.h>
#include <imgui/imgui_internal.h>
#include <ImGuizmo/ImGuizmo.h>

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
        // _texture = Texture2D::create("C:\\Users\\Willy\\Desktop\\TheEngine\\TheEngine\\resource\\texture\\instagram.png");
        // _texture1 = Texture2D::create("C:\\Users\\Willy\\Desktop\\TheEngine\\TheEngine\\resource\\texture\\logo.png");
#endif

        FrameBufferSpec spec = { 1280, 960 };
        _framebuffer = FrameBuffer::create( spec );

        // make sure the ViewportSize of the first frame is valid (not (0, 0))
        // this is going to be corrected after the first frame is rendered
        ViewportSize = { (float)spec.width, (float)spec.height };

        // scene
        _activeScene = CreateRef<Scene>();
        _hierarchyPanel.setContext( _activeScene );

        // editor camera
        _editorCamera = EditorCamera::create();

        CORE_INFO( "Editor Layer Initialized" );
    }

    void EditorLayer::onDetach() {
        dockspaceOpen = false;
        window_flags = ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDocking;
        dockspace_flags = ImGuiDockNodeFlags_None;
    }

    void EditorLayer::onUpdate(const TimeStep& deltaTime) {
        // update frame buffer if necessary
        const auto& fbspec = _framebuffer->spec();
        if ( (uint32_t)ViewportSize.x != fbspec.width || (uint32_t)ViewportSize.y != fbspec.height ) {
            _framebuffer->resize( (uint32_t)ViewportSize.x, (uint32_t)ViewportSize.y );
            _activeScene->onResize(ViewportSize.x, ViewportSize.y);
            _editorCamera->setViewportSize({ ViewportSize.x, ViewportSize.y });
        }

        _framebuffer->bind();
        // _activeScene->onUpdate( deltaTime, ViewportFocused );
        _editorCamera->onUpdate(deltaTime);
        _activeScene->onUpdateEditor(deltaTime, _editorCamera);
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
        ImGuiStyle& style = ImGui::GetStyle();
        float temp = style.WindowMinSize.x;
        style.WindowMinSize.x = 360.0f;
        ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f), dockspace_flags);
        style.WindowMinSize.x = temp;

        if (ImGui::BeginMenuBar())
        {
            if (ImGui::BeginMenu("File"))
            {
                if (ImGui::MenuItem("New", "Ctrl+N")) this->newScene();
                ImGui::Separator();
                if (ImGui::MenuItem("Open ...", "Ctrl+O")) this->loadScene();
                ImGui::Separator();
                if (ImGui::MenuItem("Save", "Ctrl+S")) this->saveScene();
                ImGui::Separator();
                if (ImGui::MenuItem("Save As ...", "Ctrl+Shift+S")) this->saveNewScene();
                ImGui::Separator();
                if (ImGui::MenuItem("Exit")) App::close();

                ImGui::EndMenu();
            }
            if (ImGui::BeginMenu("View")) {
                if (ImGui::MenuItem( "Zoom In",  "cmd +" )) ImGuiLayer::fontZoomIn();
                if (ImGui::MenuItem( "Zoom Out", "cmd -" )) ImGuiLayer::fontZoomOut();

                ImGui::EndMenu();
            }
            ImGui::EndMenuBar();
        }

        _hierarchyPanel.onImGui();

        // test window
        {
            auto stat = Renderer2D::stat();
            ImGui::Begin("Test");
            ImGui::Text( "framerate: %.0f", ImGui::GetIO().Framerate );
            ImGui::Text( "drawCalls: %d", stat.drawCalls );
            ImGui::Text( "quadCount: %d", stat.quadCount );
            ImGui::End();
        }

        // Viewport Window
        {
            // remove the tab bar of the view port, forces the window to stay docked if its already docked
            // static ImGuiWindowClass window_class;
            // window_class.DockNodeFlagsOverrideSet = ImGuiDockNodeFlags_NoTabBar;
            // ImGui::SetNextWindowClass( &window_class );

            // Info: set to zero padding on viewport window and make it non-collapsable
            static ImGuiWindowFlags flags = ImGuiWindowFlags_NoCollapse;
            ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
            ImGui::Begin("View Port", NULL, flags);
            ImGui::PopStyleVar();

            ViewportSize      = ImGui::GetContentRegionAvail();
            ViewportFocused   = ImGui::IsWindowFocused();
            ViewportHovered   = ImGui::IsWindowHovered();

            // events should be propagated only when the viewport is focused and hovered!
            if ( ViewportFocused || ViewportHovered ) ImGuiLayer::setNoBlockEvent();
            else                                      ImGuiLayer::setBlockEvent();

            ImGui::Image( (void*)(intptr_t)_framebuffer->colorAttachmentID(),
                          ViewportSize, ImVec2(0, 1), ImVec2(1, 0) );

            // Gizmo
            Entity selectedEntity = _hierarchyPanel.getSelectedEntity();
            if (selectedEntity && _gizmoOP) {
                ImGuizmo::SetOrthographic(false);
                ImGuizmo::SetDrawlist();
                ImGuizmo::SetRect(ImGui::GetWindowPos().x, ImGui::GetWindowPos().y, ImGui::GetWindowWidth(), ImGui::GetWindowHeight());

                const auto& cameraView = _editorCamera->getView();
                const auto& cameraProjection = _editorCamera->getProjection();

                auto& transformComponent = selectedEntity.get<TransformComponent>();
                glm::mat4 transform = transformComponent.transform();
                
                bool snap = Input::keyPressed(Key::LEFT_CONTROL);
                float snapValue = 0.5f; // for translation and scale
                if (_gizmoOP == ImGuizmo::OPERATION::ROTATE) snapValue = 45.0f;
                float snapValues[3] = { snapValue, snapValue, snapValue };
                ImGuizmo::Manipulate(&cameraView[0][0], &cameraProjection[0][0], _gizmoOP, ImGuizmo::LOCAL,
                                     &transform[0][0], nullptr, snap ? snapValues : nullptr);
            
                if (ImGuizmo::IsUsing()) {
                    math::decomposeTransform(transform, transformComponent.translation,
                                                        transformComponent.rotation,
                                                        transformComponent.scale);
                }
            }

            ImGui::End();
        }

        // ImGui::ShowDemoWindow();

        // end dockspace
        ImGui::End();
    }

    void EditorLayer::newScene() {
        _activeScene = Scene::create();
        _activeScene->onResize(ViewportSize.x, ViewportSize.y);
        _hierarchyPanel.setContext(_activeScene);
    }

    void EditorLayer::saveScene() {
        if (_activeScene->getFilePath().size()) {
            Serializer serializer(_activeScene);
            serializer.serialize(_activeScene->getFilePath().c_str());
        }
        else this->saveNewScene();
    }

    void EditorLayer::saveNewScene() {
        auto file = FileDialog::fileExplorer(false, "Scene File(*.yaml/yml)\0*.yaml;*.yml\0");
        if (file.size()) {
            Serializer serializer(_activeScene);
            serializer.serialize(file.c_str());
            _activeScene->setFilePath(file.c_str());
        }
    }

    void EditorLayer::loadScene() {
        auto file = FileDialog::fileExplorer(true, "Scene File(*.yaml/yml)\0*.yaml;*.yml\0");
        if (file.size()) {
            _activeScene = Scene::create();

            Serializer serializer(_activeScene);
            serializer.deserialize(file.c_str());

            _activeScene->onResize(ViewportSize.x, ViewportSize.y);
            _hierarchyPanel.setContext(_activeScene);
        }
    }

    void EditorLayer::onEvent(Event& event) {
        _activeScene->onEvent(event);
        _editorCamera->onEvent(event);

        EventDispatcher dispatcher(event);
        dispatcher.dispatch<KeyPressedEvent>(CORE_BIND_EVENT_FN(EditorLayer::onKeyPressed));
    }

    bool EditorLayer::onKeyPressed(KeyPressedEvent& event) {
        static Mod_t SHIFT_CTRL_ALT_BITMASK = ModKey::MOD_SHIFT_BIT | ModKey::MOD_CONTROL_BIT | ModKey::MOD_ALT_BIT;
        
        if (event.repeat()) return false;
        
        auto modFlags = event.mods() & SHIFT_CTRL_ALT_BITMASK;
        switch (event.key()) {
            case Key::S: // TODO
            {
                if (modFlags == ModKey::MOD_CONTROL_BIT) { // only Ctrl is pressed
                    this->saveScene();
                }
                else if (modFlags == (ModKey::MOD_CONTROL_BIT | ModKey::MOD_SHIFT_BIT)) { // Ctrl + Shift
                    this->saveNewScene();
                }
                break;
            }
            case Key::O:
            {
                if (modFlags == ModKey::MOD_CONTROL_BIT) { // only Ctrl is pressed
                    this->loadScene();
                }
                break;
            }
            case Key::N:
            {
                if (modFlags == ModKey::MOD_CONTROL_BIT) { // only Ctrl is pressed
                    this->newScene();
                }
                break;
            }
            case Key::Q: // disbale gizmo
            {
                if (!modFlags) { // no other key is pressed
                    _gizmoOP = (ImGuizmo::OPERATION)0;
                }
                break;
            }
            case Key::W:
            {
                if (!modFlags) {
                    _gizmoOP = ImGuizmo::OPERATION::TRANSLATE;
                }
                break;
            }
            case Key::E:
            {
                if (!modFlags) {
                    _gizmoOP = ImGuizmo::OPERATION::ROTATE;
                }
                break;
            }
            case Key::R:
            {
                if (!modFlags) {
                    _gizmoOP = ImGuizmo::OPERATION::SCALE;
                }
                break;
            }
            default: return false;
        }
        return true;
    }
}
