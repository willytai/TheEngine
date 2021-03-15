#include "GLcontext.h"
#include "util/log.h"
#include "glad/glad.h"
#include "backend/backend.h"

namespace Engine7414
{
    OpenGLContext::OpenGLContext(GLFWwindow* handle)
        : _handle(handle) {}

    void OpenGLContext::init() {
        glfwMakeContextCurrent( _handle );
        // initialize opengl
        if ( !gladLoadGLLoader((GLADloadproc)glfwGetProcAddress) ) {
            OPENGL_ERROR( "Failed to initialize GLAD." );
            BACKEND_ASSERT( false, "error net yet handled, aborting..." );
        }

        BACKEND_INFO( "OpenGL Info" );
        BACKEND_INFO( "\tVendor: {}", glGetString( GL_VENDOR ) );
        BACKEND_INFO( "\tVersion: {} ({}.{})", glGetString( GL_VERSION ), GLVersion.major, GLVersion.minor );
        BACKEND_INFO( "\tRenderer: {}", glGetString( GL_RENDERER ) );
        BACKEND_INFO( "\tGLSL Version: {}", glGetString( GL_SHADING_LANGUAGE_VERSION ) );
        BACKEND_INFO( "\tz-buffer: Enabled (default)" );

        glEnable( GL_DEPTH_TEST );
    }

    void OpenGLContext::swapBuffers() {
        glfwSwapBuffers( _handle );
    }
}
