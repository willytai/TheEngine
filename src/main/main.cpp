#define GLFW_INCLUDE_NONE
#include "test.h"
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

    if ( (window = glfwCreateWindow( 1280, 960, "Test Window", NULL, NULL )) != NULL ) {
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

    // z-buffer
    GLCall( glEnable( GL_DEPTH_TEST ) );

    // enable blending
    GLCall( glEnable( GL_BLEND ) );
    GLCall( glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA ) );

    // textures
    // Texture texture( "./resource/texture/logo.png" );
    // texture.unbind();
    // texture.bind();
    // shader.setUniform1i( "u_texture", 0 );

    // renderer
    Renderer renderer;
    test::testPool::init( window );

    // ImGui
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGui::StyleColorsDark();
    ImGui_ImplGlfw_InitForOpenGL( window, true );
    ImGui_ImplOpenGL3_Init( "#version 330 core" );

    double lastTime = glfwGetTime();
    while ( !glfwWindowShouldClose(window) ) {
        renderer.clear();

        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        {   // since ImGui window and tests are handled after
            // things in the vertex buffer are rendered, this window
            // and all the tests' operations are gonna overwrite what's
            // already on the screen (which is what I intended to design)
            ImGui::Begin("ImGui Window");
#ifdef BUILD_TEST
            double curTime = glfwGetTime();
            float deltaTime = float(curTime - lastTime);
            lastTime = curTime;
            ImGui::Text( "Tests" );
            test::testPool::test( deltaTime );
#endif
            ImGui::NewLine();
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
