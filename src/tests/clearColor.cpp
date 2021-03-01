#include "test.h"

namespace test
{
    testClearColor::testClearColor(const char* name) {
        ::test::testPool::updateWindowTitle( name );
    }

    testClearColor::~testClearColor() {

    }

    void testClearColor::onUpdate(float time) {

    }

    void testClearColor::onRenderer() {
        GLCall( glClearColor( _color[0], _color[1], _color[2], _color[3] ) );
        GLCall( glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT ) );
    }

    void testClearColor::onImGui() {
        if ( ImGui::Button( "<-" ) ) {
            testPool::reset();
        }
        ImGui::ColorEdit4( "Color", _color );
    }
}
