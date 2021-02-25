#include "test.h"
#include "imgui.h"

namespace test
{
    void testPool::Register() {
#ifdef BUILD_TEST
        get().addTest<testClearColor> ( "clear color",  "clearColor" );
        get().addTest<testColoredCube>( "colored cube", "coloredCube" );
#else
        OPENGL_INFO( "Tests disabled." );
#endif
    }

    void testPool::update() {
        get().onImGui();
        get().onRenderer();
    }

    void testPool::reset() {
        delete get()._curTest;
        get()._curTest = NULL;
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
