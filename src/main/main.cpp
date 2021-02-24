#define GLFW_INCLUDE_NONE
#include "renderer.h"
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include <GLFW/glfw3.h>
#include <glm/gtc/matrix_transform.hpp>

#if defined(__clang__)
    #pragma clang diagnostic push
    #pragma clang diagnostic ignored "-Wunused-parameter"
#elif defined(__GNUC__)
    #pragma GCC diagnostic push
    #pragma GCC diagnostic ignored "-Wunused-parameter"
#else
    #error "Compiler Not Supported!"
#endif
int main(int argc, char *argv[])
#if defined(__clang__)
    #pragma clang diagnostic pop
#elif defined(__GNUC__)
    #pragma GCC diagnostic pop
#else
    #error "Compiler Not Supported!"
#endif
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
         0.0f,   0.0f,   0.0f, 0.0f,
         240.0f, 0.0f,   1.0f, 0.0f,
         240.0f, 240.0f, 1.0f, 1.0f,
         0.0f,   240.0f, 0.0f, 1.0f
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
    glm::mat4 projection = glm::ortho( 0.0f, 1280.0f, 0.0f, 960.0f, -1.0f, 1.0f );
    // camara (move right, object move left)
    glm::mat4 view = glm::translate( glm::mat4(1.0f), glm::vec3( 0.0f, 0.0f, 0.0f ) );

    // shaders
    Shader shader( "./resource/shader/vertex.glsl", "./resource/shader/fragment.glsl");
    shader.bind();

    // textures
    Texture texture( "./resource/texture/logo.png" );
    texture.bind();
    shader.setUniform1i( "u_texture", 0 );

    // renderer
    Renderer renderer;

    // ImGui
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGui::StyleColorsDark();
    ImGui_ImplGlfw_InitForOpenGL( window, true );
    ImGui_ImplOpenGL3_Init( "#version 330 core" );

    va.unbind();
    vb.unbind();
    ib.unbind();
    shader.unbind();

    float r_channel = 1.0f;
    float intv = 0.05f;
    glm::vec3 translation( 0.0f, 0.0f, 0.0f );

    while ( !glfwWindowShouldClose(window) ) {
        renderer.clear();

        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        // place model at the origin
        glm::mat4 model = glm::translate( glm::mat4(1.0f), translation );
        glm::mat4 mvp = projection * view * model;

        shader.bind();
        shader.setUniform4f( "u_color", r_channel, 0.3f, 0.8f, 1.0f );
        shader.setUniformMat4f( "u_MVP", mvp );

        renderer.draw( va, ib, shader );

        if ( r_channel > 1.0f ) intv = -0.05f;
        else if ( r_channel < 0.0f ) intv = 0.05f;
        r_channel += intv;

        {
            ImGui::Begin("ImGui Window");
            ImGui::SliderFloat("x_position", &translation.x, 0.0f, 1280.0f-240.0f);
            ImGui::SliderFloat("y_position", &translation.y, 0.0f, 960.0f-240.0f);
            ImGui::Text("Application average %.3f ms/frame (%.1f FPS)",
                        1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
            ImGui::End();
        }

        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData( ImGui::GetDrawData() );

        glfwSwapBuffers( window );
        glfwPollEvents();
    }

    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    glfwDestroyWindow( window );
    glfwTerminate();
    return 0;
}
