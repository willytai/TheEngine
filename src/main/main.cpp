#define GLFW_INCLUDE_NONE
#include "renderer.h"
#include <GLFW/glfw3.h>
#include <glm/gtc/matrix_transform.hpp>

int main(int argc, char *argv[])
{
    util::Log::init( 4 );

    GLFWwindow* window = NULL;

    if ( glfwInit() ) {
        GLFW_INFO( "Successfully Initialized." );

        glfwWindowHint( GLFW_CONTEXT_VERSION_MAJOR, 3 );
        glfwWindowHint( GLFW_CONTEXT_VERSION_MINOR, 3 );
        glfwWindowHint( GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE );
        glfwWindowHint( GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE );
    }
    else {
        GLFW_ERROR( "Initialization Failed." );
        return -1;
    }

    if ( (window = glfwCreateWindow( 1280, 960, "test window", NULL, NULL )) != NULL ) {
        GLFW_INFO( "window created." );
    }
    else {
        GLFW_ERROR( "unable to create window." );
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent( window );
    glfwSwapInterval(1);

    if ( !gladLoadGLLoader((GLADloadproc)glfwGetProcAddress) ) {
        GLFW_ERROR( "Failed to initialize GLAD." );
        exit(EXIT_FAILURE);
    }

    // enable blending
    GLCall( glEnable( GL_BLEND ) );
    GLCall( glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA ) );

    float positions[] = {
        -0.5f, -0.5f, 0.0f, 0.0f,
         0.5f, -0.5f, 1.0f, 0.0f,
         0.5f,  0.5f, 1.0f, 1.0f,
        -0.5f,  0.5f, 0.0f, 1.0f
    };

    unsigned int indices[] = {
        0, 1, 2,
        0, 2, 3
    };

    // vertex buffer object
    VertexBuffer vb( positions, 4*4*sizeof(float) );

    // vertex array object
    VertexBufferLayout layout;
    layout.push<GLfloat>(2);
    layout.push<GLfloat>(2);
    VertexArray va;
    va.addLayout( vb, layout );

    // index buffer object
    IndexBufferUI ib( indices, 6 );

    // this shold be determined right after window creation
    // https://en.wikipedia.org/wiki/Orthographic_projection
    glm::mat4 projection = glm::ortho( -2.0f, 2.0f, -1.5f, 1.5f, -1.0f, 1.0f );
    // camara (move right, object move left)
    glm::mat4 view = glm::translate( glm::mat4(1.0f), glm::vec3( -1.0f, 0.0f, 0.0f ) );
    // place model at the origin
    glm::mat4 model = glm::mat4(1.0f);
    glm::mat4 mvp = projection * view * model;

    // shaders
    Shader shader( "./resource/shader/vertex.glsl", "./resource/shader/fragment.glsl");
    shader.bind();
    shader.setUniformMat4f( "u_MVP", mvp );

    // textures
    Texture texture( "./resource/texture/logo.png" );
    texture.bind();
    shader.setUniform1i( "u_texture", 0 );

    // renderer
    Renderer renderer;

    va.unbind();
    vb.unbind();
    ib.unbind();
    shader.unbind();

    float r_channel = 1.0f;
    float intv = 0.05f;

    while ( !glfwWindowShouldClose(window) ) {
        renderer.clear();

        shader.bind();
        shader.setUniform4f( "u_color", r_channel, 0.3f, 0.8f, 1.0f );

        renderer.draw( va, ib, shader );

        if ( r_channel > 1.0f ) intv = -0.05f;
        else if ( r_channel < 0.0f ) intv = 0.05f;
        r_channel += intv;

        glfwSwapBuffers( window );
        glfwPollEvents();
    }

    glfwDestroyWindow( window );

    glfwTerminate();
    return 0;
}
