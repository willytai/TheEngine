#include "GLcontext.h"
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
            case GL_DEBUG_SOURCE_API:             BACKEND_ERROR( "Source: API" ); break;
            case GL_DEBUG_SOURCE_WINDOW_SYSTEM:   BACKEND_ERROR( "Source: Window System" ); break;
            case GL_DEBUG_SOURCE_SHADER_COMPILER: BACKEND_ERROR( "Source: Shader Compiler" ); break;
            case GL_DEBUG_SOURCE_THIRD_PARTY:     BACKEND_ERROR( "Source: Third Party" ); break;
            case GL_DEBUG_SOURCE_APPLICATION:     BACKEND_ERROR( "Source: Application" ); break;
            case GL_DEBUG_SOURCE_OTHER:           BACKEND_ERROR( "Source: Other" ); break;
        }

        switch (type)
        {
            case GL_DEBUG_TYPE_ERROR:               BACKEND_ERROR( "Type: Error" ); break;
            case GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR: BACKEND_ERROR( "Type: Deprecated Behaviour" ); break;
            case GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR:  BACKEND_ERROR( "Type: Undefined Behaviour" ); break;
            case GL_DEBUG_TYPE_PORTABILITY:         BACKEND_ERROR( "Type: Portability" ); break;
            case GL_DEBUG_TYPE_PERFORMANCE:         BACKEND_ERROR( "Type: Performance" ); break;
            case GL_DEBUG_TYPE_MARKER:              BACKEND_ERROR( "Type: Marker" ); break;
            case GL_DEBUG_TYPE_PUSH_GROUP:          BACKEND_ERROR( "Type: Push Group" ); break;
            case GL_DEBUG_TYPE_POP_GROUP:           BACKEND_ERROR( "Type: Pop Group" ); break;
            case GL_DEBUG_TYPE_OTHER:               BACKEND_ERROR( "Type: Other" ); break;
        }

        switch (severity)
        {
            case GL_DEBUG_SEVERITY_HIGH:         BACKEND_ERROR( "Severity: high" ); break;
            case GL_DEBUG_SEVERITY_MEDIUM:       BACKEND_ERROR( "Severity: medium" ); break;
            case GL_DEBUG_SEVERITY_LOW:          BACKEND_ERROR( "Severity: low" ); break;
            case GL_DEBUG_SEVERITY_NOTIFICATION: BACKEND_ERROR( "Severity: notification" ); break;
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

#ifdef __APPLE__
        if ( GLVersion.major < 4 || GLVersion.minor < 1 ) {
            BACKEND_WARN( "Engine7414 does not guarantee full functionality for OpenGL version lower than 4.1 on your OS, program might crash!" );
        }
#else
        if ( GLVersion.major < 4 || GLVersion.minor < 5 ) {
            BACKEND_WARN( "Engine7414 does not guarantee full functionality for OpenGL version lower than 4.5 on your OS, program might crash!" );
        }
#endif

#if defined(_WIN64) && defined(ENGINE_DEBUG)
        int flags; glGetIntegerv(GL_CONTEXT_FLAGS, &flags);
        if (flags & GL_CONTEXT_FLAG_DEBUG_BIT)
        {
            glEnable(GL_DEBUG_OUTPUT);
            glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
            glDebugMessageCallback(glDebugOutput, 0);
            glDebugMessageControl(GL_DEBUG_SOURCE_API,
                GL_DEBUG_TYPE_ERROR,
                GL_DEBUG_SEVERITY_HIGH,
                0, nullptr, GL_TRUE);
            BACKEND_INFO("\tDebug Context: Enabled (default)");
        }
#elif defined(ENGINE_DEBUG)
        BACKEND_INFO("\tDebug Context: Disabled (debug context not supported on your platform)");
#else
        BACKEND_INFO("\tDebug Context: Disabled (release mode)");
#endif
    }

    void OpenGLContext::swapBuffers() {
        glfwSwapBuffers( _handle );
    }
}
