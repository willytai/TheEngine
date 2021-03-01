#include "test.h"

namespace test
{
    testColoredCube::testColoredCube(const char* name) :
        __shader( "./resource/shader/pos4d_color3d/vertex.glsl",
                  "./resource/shader/pos4d_color3d/fragment.glsl") {
        ::test::testPool::updateWindowTitle( name );

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

        // vertex buffer object
        VertexBuffer vb( positions, 8*(4+3)*sizeof(GLfloat) );

        // vertex array object
        VertexBufferLayout layout;
        layout.push<GLfloat>(4);
        layout.push<GLfloat>(3);
        __va.addLayout( vb, layout );

        // index buffer object
        __ib = new IndexBufferUI( indices, 36 );

        // projection
        __perspective = glm::perspective( glm::radians(45.0f),
                                          1280.0f / 960.f,
                                          0.1f,
                                          100.0f
                                         );
        __va.unbind();

        __m_translation = glm::vec3( 0.0f, 0.0f, 0.0f );
        __m_rotation    = glm::vec3( 0.0f, 0.0f, 0.0f );
        __m_scale       = 1.0f;
        __camera_height = 5.0f;
    }

    testColoredCube::~testColoredCube() {
        delete __ib;
    }

    void testColoredCube::onUpdate(float time) {

    }

    void testColoredCube::onRenderer() {

        // model matrix
        glm::mat4 model = glm::translate( glm::mat4(1.0f), __m_translation )
                        * glm::rotate( glm::mat4(1.0f), __m_rotation.x, glm::vec3(1.0f, 0.0f, 0.0f) )
                        * glm::rotate( glm::mat4(1.0f), __m_rotation.y, glm::vec3(0.0f, 1.0f, 0.0f) )
                        * glm::rotate( glm::mat4(1.0f), __m_rotation.z, glm::vec3(0.0f, 0.0f, 1.0f) )
                        * glm::scale(  glm::mat4(1.0f), glm::vec3( __m_scale, __m_scale, __m_scale ) );
        // camara
        glm::mat4 view = glm::lookAt( glm::vec3( 0.0f, __camera_height, 10.0f ), // position
                                      glm::vec3( 0.0f, 0.0f, 0.0f ),             // looks at the origin
                                      glm::vec3( 0.0f, 1.0f, 0.0f )              // head is up
                                    );


        __shader.bind();
        __shader.setUniformMat4f( "u_model", model );
        __shader.setUniformMat4f( "u_view", view );
        __shader.setUniformMat4f( "u_projection", __perspective );

        Renderer renderer;
        renderer.draw( __va, *__ib, __shader );
    }

    void testColoredCube::onImGui() {
        if ( ImGui::Button( "<-" ) ) {
            testPool::reset();
        }
        else {
            ImGui::SliderFloat3( "xyz position",  &__m_translation.x, -5.0f, 5.0f );
            ImGui::SliderFloat3( "xyz rotation",  &__m_rotation.x,     0.0f, 10.0f );
            ImGui::SliderFloat(  "scale",         &__m_scale,          1.0f, 5.0f );
            ImGui::SliderFloat(  "camera height", &__camera_height,    2.0f, 10.0f );
        }
    }
}
