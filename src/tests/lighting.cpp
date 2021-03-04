#include "test.h"

namespace test
{
    static glm::vec4 __ObjPos__(0.0f, 0.0f, 0.0f, 1.0f);
    static float degreePerIntv = glm::radians( 1.0f );

    testLighting::testLighting(const char* name) :
        __shader( "./resource/shader/lighting_Phong/vertex.glsl",
                  "./resource/shader/lighting_Phong/fragment.glsl" ),
        __ambient(0.2f),
        __specularStrength(0.5f),
        __shininess(32),
        __lightPosOffset(0.0f, 0.0f, 20.0f),
        __lightColor(1.0f, 1.0f, 1.0f),
        __objColor(0.8f, 0.0f, 0.5f) {
        ::test::testPool::updateWindowTitle( name );

        __camera = new Camera( testPool::getGLFWwindow(), glm::vec3(20.0f, 20.0f, 50.0f) );

        GLfloat cubeVertices[] = {
             // face of the cube         // normals
             -10.0f, -10.0f,  10.0f, 1.0f,  0.0f,  0.0f,  1.0f,
              10.0f, -10.0f,  10.0f, 1.0f,  0.0f,  0.0f,  1.0f,
              10.0f,  10.0f,  10.0f, 1.0f,  0.0f,  0.0f,  1.0f,
             -10.0f,  10.0f,  10.0f, 1.0f,  0.0f,  0.0f,  1.0f,
             // tail of the cube
             -10.0f, -10.0f, -10.0f, 1.0f,  0.0f,  0.0f, -1.0f,
              10.0f, -10.0f, -10.0f, 1.0f,  0.0f,  0.0f, -1.0f,
              10.0f,  10.0f, -10.0f, 1.0f,  0.0f,  0.0f, -1.0f,
             -10.0f,  10.0f, -10.0f, 1.0f,  0.0f,  0.0f, -1.0f,
             // left of the cube
             -10.0f, -10.0f, -10.0f, 1.0f, -1.0f,  0.0f,  0.0f,
             -10.0f, -10.0f,  10.0f, 1.0f, -1.0f,  0.0f,  0.0f,
             -10.0f,  10.0f,  10.0f, 1.0f, -1.0f,  0.0f,  0.0f,
             -10.0f,  10.0f, -10.0f, 1.0f, -1.0f,  0.0f,  0.0f,
             // right of the cube
              10.0f, -10.0f, -10.0f, 1.0f,  1.0f,  0.0f,  0.0f,
              10.0f, -10.0f,  10.0f, 1.0f,  1.0f,  0.0f,  0.0f,
              10.0f,  10.0f,  10.0f, 1.0f,  1.0f,  0.0f,  0.0f,
              10.0f,  10.0f, -10.0f, 1.0f,  1.0f,  0.0f,  0.0f,
             // top of the cube
             -10.0f,  10.0f, -10.0f, 1.0f,  0.0f,  1.0f,  0.0f,
             -10.0f,  10.0f,  10.0f, 1.0f,  0.0f,  1.0f,  0.0f,
              10.0f,  10.0f,  10.0f, 1.0f,  0.0f,  1.0f,  0.0f,
              10.0f,  10.0f, -10.0f, 1.0f,  0.0f,  1.0f,  0.0f,
             // bottom of the cube
             -10.0f, -10.0f, -10.0f, 1.0f,  0.0f, -1.0f,  0.0f,
             -10.0f, -10.0f,  10.0f, 1.0f,  0.0f, -1.0f,  0.0f,
              10.0f, -10.0f,  10.0f, 1.0f,  0.0f, -1.0f,  0.0f,
              10.0f, -10.0f, -10.0f, 1.0f,  0.0f, -1.0f,  0.0f,
        };

        GLfloat lightSourceVertices[] = {
             // face of the cube         // normals
             -0.5f, -0.5f,  0.5f, 1.0f,  0.0f,  0.0f, -1.0f,
              0.5f, -0.5f,  0.5f, 1.0f,  0.0f,  0.0f, -1.0f,
              0.5f,  0.5f,  0.5f, 1.0f,  0.0f,  0.0f, -1.0f,
             -0.5f,  0.5f,  0.5f, 1.0f,  0.0f,  0.0f, -1.0f,
             // tail of the cube
             -0.5f, -0.5f, -0.5f, 1.0f,  0.0f,  0.0f,  1.0f,
              0.5f, -0.5f, -0.5f, 1.0f,  0.0f,  0.0f,  1.0f,
              0.5f,  0.5f, -0.5f, 1.0f,  0.0f,  0.0f,  1.0f,
             -0.5f,  0.5f, -0.5f, 1.0f,  0.0f,  0.0f,  1.0f,
             // left of the cube
             -0.5f, -0.5f, -0.5f, 1.0f,  1.0f,  0.0f,  0.0f,
             -0.5f, -0.5f,  0.5f, 1.0f,  1.0f,  0.0f,  0.0f,
             -0.5f,  0.5f,  0.5f, 1.0f,  1.0f,  0.0f,  0.0f,
             -0.5f,  0.5f, -0.5f, 1.0f,  1.0f,  0.0f,  0.0f,
             // right of the cube
              0.5f, -0.5f, -0.5f, 1.0f, -1.0f,  0.0f,  0.0f,
              0.5f, -0.5f,  0.5f, 1.0f, -1.0f,  0.0f,  0.0f,
              0.5f,  0.5f,  0.5f, 1.0f, -1.0f,  0.0f,  0.0f,
              0.5f,  0.5f, -0.5f, 1.0f, -1.0f,  0.0f,  0.0f,
             // top of the cube
             -0.5f,  0.5f, -0.5f, 1.0f,  0.0f, -1.0f,  0.0f,
             -0.5f,  0.5f,  0.5f, 1.0f,  0.0f, -1.0f,  0.0f,
              0.5f,  0.5f,  0.5f, 1.0f,  0.0f, -1.0f,  0.0f,
              0.5f,  0.5f, -0.5f, 1.0f,  0.0f, -1.0f,  0.0f,
             // bottom of the cube
             -0.5f, -0.5f, -0.5f, 1.0f,  0.0f,  1.0f,  0.0f,
             -0.5f, -0.5f,  0.5f, 1.0f,  0.0f,  1.0f,  0.0f,
              0.5f, -0.5f,  0.5f, 1.0f,  0.0f,  1.0f,  0.0f,
              0.5f, -0.5f, -0.5f, 1.0f,  0.0f,  1.0f,  0.0f,
        };

        GLuint indices[] = {
            0, 1, 2,
            0, 2, 3,
            4, 5, 6,
            4, 6, 7,
            8, 9, 10,
            8, 10, 11,
            12, 13, 14,
            12, 14, 15,
            16, 17, 18,
            16, 18, 19,
            20, 21, 22,
            20, 22, 23
        };

        VertexBuffer vbCube( cubeVertices, 6*4*(4+3)*sizeof(GLfloat) );
        VertexBuffer vbLight( lightSourceVertices, 6*4*(4+3)*sizeof(GLfloat) );
        VertexBufferLayout layout;
        layout.push<GLfloat>(4);
        layout.push<GLfloat>(3);
        __ib = new IndexBufferUI( indices, 36 );
        __vaCube.addLayout( vbCube, layout );
        __vaCube.unbind();
        __vaLight.addLayout( vbLight, layout );
        __vaLight.unbind();
    }

    testLighting::~testLighting() {
        delete __camera;
        delete __ib;
    }

    void testLighting::onUpdate(float time) {
        __camera->onUpdate( time );
        __lightPosOffset = (glm::rotate( glm::mat4(1.0f), degreePerIntv, glm::vec3(0.0f, 1.0f, 0.0f) ) *
                           glm::vec4( __lightPosOffset, 1.0f )).xyz();
    }

    void testLighting::onRenderer() {
        Renderer renderer;
        __shader.bind();
        __shader.setUniform4f( "u_cameraPos", glm::vec4(__camera->getPos(), 1.0f ) );
        __shader.setUniform1f( "u_specularStrength", __specularStrength );
        __shader.setUniform1i( "u_shininess", __shininess );
        __shader.setUniform4f( "u_lightPos", __ObjPos__+glm::vec4(__lightPosOffset, 0.0f) );
        __shader.setUniform3f( "u_lightColor", __lightColor );
        __shader.setUniformMat4f( "u_view", __camera->getView() );
        __shader.setUniformMat4f( "u_projection", __camera->getPerspective() );

        // light source
        __shader.setUniform3f( "u_ambient", 0.0f, 0.0f, 0.0f );
        __shader.setUniform3f( "u_objColor", __lightColor );
        __shader.setUniformMat4f( "u_model", glm::translate( glm::mat4(1.0f), __ObjPos__.xyz()+__lightPosOffset ) );
        renderer.drawElement( __vaLight, *__ib, __shader );

        // cube
        __shader.setUniform3f( "u_ambient", __ambient, __ambient, __ambient );
        __shader.setUniform3f( "u_objColor", __objColor );
        __shader.setUniformMat4f( "u_model", glm::translate( glm::mat4(1.0f), __ObjPos__.xyz() ) );
        renderer.drawElement( __vaCube, *__ib, __shader );
    }

    void testLighting::onImGui() {
        if ( ImGui::Button( "<-" ) ) {
            testPool::reset();
        }
        else {
            ImGui::ColorEdit3( "light color", &__lightColor[0] );
            ImGui::ColorEdit3( "cube color", &__objColor[0] );
            ImGui::SliderFloat( "ambient intensity", &__ambient,          0.1f,  0.3f );
            ImGui::SliderFloat( "specular strength", &__specularStrength, 0.1f,  1.0f );
            ImGui::SliderInt(   "shininess",         &__shininess,        2,     256 );
            ImGui::SliderFloat( "movement speed",    __camera->getMovementSpeedPtr(), 5.0f, 10.0f );
            ImGui::SliderFloat( "mouse sensitivity", __camera->getSensitivityPtr(),   5.0f, 10.0f );
        }
    }
}

