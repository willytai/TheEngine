#include "test.h"

namespace test
{
    testCamera::testCamera(const char* name) :
        __shader( "./resource/shader/pos4d_color3d/vertex.glsl",
                  "./resource/shader/pos4d_color3d/fragment.glsl") {
        ::test::testPool::updateWindowTitle( name );

        __camera = new Camera( testPool::getGLFWwindow() );

        GLfloat positions[] = {
             // face of the cube
             -1.0f, -1.0f,  1.0f, 1.0f,  0.583f,  0.771f,  0.014f,
              1.0f, -1.0f,  1.0f, 1.0f,  0.822f,  0.569f,  0.201f,
              1.0f,  1.0f,  1.0f, 1.0f,  0.559f,  0.436f,  0.730f,
             -1.0f,  1.0f,  1.0f, 1.0f,  0.195f,  0.548f,  0.859f,
             // tail of the cube
             -1.0f, -1.0f, -1.0f, 1.0f,  0.140f,  0.616f,  0.489f,
              1.0f, -1.0f, -1.0f, 1.0f,  0.543f,  0.021f,  0.978f,
              1.0f,  1.0f, -1.0f, 1.0f,  0.055f,  0.953f,  0.042f,
             -1.0f,  1.0f, -1.0f, 1.0f,  0.225f,  0.587f,  0.040f
        };

        GLuint indices[] = {
            0, 1, 2,
            0, 2, 3,
            4, 5, 6,
            4, 6, 7,
            3, 2, 6,
            3, 6, 7,
            0, 1, 5,
            0, 5, 4,
            0, 4, 7,
            0, 7, 3,
            1, 5, 6,
            1, 6, 2
        };

        VertexBuffer vb( positions, 8*(4+3)*sizeof(GLfloat) );
        VertexBufferLayout layout;
        layout.push<GLfloat>(4);
        layout.push<GLfloat>(3);
        __va.addLayout( vb, layout );
        __ib = new IndexBufferUI( indices, 36 );

        __va.unbind();
    }

    testCamera::~testCamera() {
        delete __camera;
        delete __ib;
    }

    void testCamera::onUpdate(float time) {
        __camera->onUpdate( time );
    }

    void testCamera::onRenderer() {
        Renderer renderer;

        __shader.bind();
        __shader.setUniformMat4f( "u_model", glm::mat4(1.0f) );
        __shader.setUniformMat4f( "u_view", __camera->getView() );
        __shader.setUniformMat4f( "u_projection", __camera->getPerspective() );
        renderer.drawElement( __va, *__ib, __shader );

        __shader.setUniformMat4f( "u_model", glm::mat4(1.0f)*glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 5.0f, 0.0f)) );
        renderer.drawElement( __va, *__ib, __shader );
    }

    void testCamera::onImGui() {
        if ( ImGui::Button( "<-" ) ) {
            testPool::reset();
        }
        else {
            ImGui::SliderFloat(  "movement speed",    __camera->getMovementSpeedPtr(), 5.0f, 10.0f );
            ImGui::SliderFloat(  "mouse sensitivity", __camera->getSensitivityPtr(),   5.0f, 10.0f );
        }
    }
}
