#include "GLcontext.h"
#include "util/log.h"
#include "glad/glad.h"
#include "backend/backend.h"

namespace Engine7414
{
    static void APIENTRY glDebugOutput(GLenum source,
                                       GLenum type,
                                       unsigned int id,
                                       GLenum severity,
                                       GLsizei length,
                                       const char *message,
                                       const void *userParam)
    {
        // ignore non-significant error/warning codes
        if(id == 131169 || id == 131185 || id == 131218 || id == 131204) return;

        BACKEND_ERROR( "Debug message ({}): {}", id, message );

        switch (source)
        {
            case GL_DEBUG_SOURCE_API:             BACKEND_ERROR( "Source: API" );
            case GL_DEBUG_SOURCE_WINDOW_SYSTEM:   BACKEND_ERROR( "Source: Window System" );
            case GL_DEBUG_SOURCE_SHADER_COMPILER: BACKEND_ERROR( "Source: Shader Compiler" );
            case GL_DEBUG_SOURCE_THIRD_PARTY:     BACKEND_ERROR( "Source: Third Party" );
            case GL_DEBUG_SOURCE_APPLICATION:     BACKEND_ERROR( "Source: Application" );
            case GL_DEBUG_SOURCE_OTHER:           BACKEND_ERROR( "Source: Other" );
        }

        switch (type)
        {
            case GL_DEBUG_TYPE_ERROR:               BACKEND_ERROR( "Type: Error" );
            case GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR: BACKEND_ERROR( "Type: Deprecated Behaviour" );
            case GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR:  BACKEND_ERROR( "Type: Undefined Behaviour" );
            case GL_DEBUG_TYPE_PORTABILITY:         BACKEND_ERROR( "Type: Portability" );
            case GL_DEBUG_TYPE_PERFORMANCE:         BACKEND_ERROR( "Type: Performance" );
            case GL_DEBUG_TYPE_MARKER:              BACKEND_ERROR( "Type: Marker" );
            case GL_DEBUG_TYPE_PUSH_GROUP:          BACKEND_ERROR( "Type: Push Group" );
            case GL_DEBUG_TYPE_POP_GROUP:           BACKEND_ERROR( "Type: Pop Group" );
            case GL_DEBUG_TYPE_OTHER:               BACKEND_ERROR( "Type: Other" );
        }

        switch (severity)
        {
            case GL_DEBUG_SEVERITY_HIGH:         BACKEND_ERROR( "Severity: high" );
            case GL_DEBUG_SEVERITY_MEDIUM:       BACKEND_ERROR( "Severity: medium" );
            case GL_DEBUG_SEVERITY_LOW:          BACKEND_ERROR( "Severity: low" );
            case GL_DEBUG_SEVERITY_NOTIFICATION: BACKEND_ERROR( "Severity: notification" );
        }
    }

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

        // z-buffer
        glEnable( GL_DEPTH_TEST );
        BACKEND_INFO( "\tz-buffer: Enabled (default)" );
    }

    void OpenGLContext::swapBuffers() {
        glfwSwapBuffers( _handle );
    }
}
