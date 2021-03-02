#include "test.h"
#include "imgui.h"

namespace test
{
    void testPool::init(GLFWwindow* window) {
#ifdef BUILD_TEST
        get().addTest<testClearColor> ( "Clear Color",     "clearColor" );
        get().addTest<testColoredCube>( "Colored Cube",    "coloredCube" );
        get().addTest<testCamera>     ( "Camera Movement", "camera" );
        get().addTest<testLighting>   ( "Lighting",        "lighting" );
        get()._window = window;
#else
        OPENGL_INFO( "Tests disabled." );
#endif
    }

    void testPool::test(float deltaTime) {
        get().onUpdate( deltaTime );
        get().onImGui();
        get().onRenderer();
    }

    void testPool::reset() {
        delete get()._curTest;
        get()._curTest = NULL;
        glfwSetWindowTitle( get()._window, "Test Window" );
    }

    void testPool::updateWindowTitle(const char* name) {
        glfwSetWindowTitle( get()._window, name );
    }

    void testPool::onUpdate(const float& deltaTime) {
        if ( _curTest ) _curTest->onUpdate( deltaTime );
    }

    void testPool::onImGui() {
        if ( _curTest ) {
            _curTest->onImGui();
            return;
        }
        for (auto& [name, test] : _list) {
            if ( ImGui::Button( name.c_str() ) ) {
                _curTest = test();
                _curTest->onImGui();
            }
        }
    }

    void testPool::onRenderer() {
        if ( _curTest ) _curTest->onRenderer();
    }
}
