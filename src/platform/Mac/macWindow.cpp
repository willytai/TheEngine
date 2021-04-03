#include "core/core.h"
#include "core/event/event.h"
#include "core/input/input.h"
#include "core/util/log.h"
#include "backend/OpenGL/GLcontext.h"
#include "platform/Mac/macWindow.h"
#include "glad/glad.h"

namespace Engine7414
{
    bool MacWindow::__glfwInitialized__ = false;

    static void GLFWErrorCallback(int error, const char* description) {
        CORE_ASSERT( false, "GLFW Error ({}): {}", error, description );
    }

    MacWindow::MacWindow(const WindowProps& props) :
        Window( props.title ),
        _glfwWindow(NULL)
    {
        _data.width = props.width;
        _data.height = props.height;

        if ( !__glfwInitialized__ ) {
            if ( glfwInit() ) {
                glfwWindowHint( GLFW_CONTEXT_VERSION_MAJOR, 4 );
                glfwWindowHint( GLFW_CONTEXT_VERSION_MINOR, 1 );
                glfwWindowHint( GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE );
                glfwWindowHint( GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE );
                glfwSetErrorCallback( GLFWErrorCallback );
            }
            else {
                GLFW_ERROR( "glfw falied to initialize!" );
                CORE_ASSERT( false, "error not yet handled, aborting..." );
            }
            __glfwInitialized__ = true;
        }

        if ( (_glfwWindow = glfwCreateWindow( props.width, props.height, props.title, NULL, NULL )) == NULL ) {
            GLFW_ERROR( "unable to create window!" );
            CORE_ASSERT( false, "glfw failed to create window, error not yet handled, aborting..." );
        }

        glfwSetInputMode( _glfwWindow, GLFW_LOCK_KEY_MODS, GLFW_TRUE ); // enable modifier key flags
        glfwSetWindowUserPointer( _glfwWindow, &_data );
        this->createContext( props.rendererBackend );

        if ( props.vsync ) this->enableVSync();
        else               this->disbaleVSync();

        CORE_INFO( "Window successfully created ({1}, {2}): \'{0}\'", props.title, props.width, props.height );

        // GLFW callbacks
        this->setCallbacks();

        // bind the window to the input handler on construction
        Input::bindWindow( this );
    }

    MacWindow::~MacWindow() {
        this->shutdown();
    }

    void MacWindow::onUpdate() {
        glfwPollEvents();
        _context->swapBuffers();
    }

    void MacWindow::setEventCallback(const eventCallbackFn& fn) {
        _data.callback = fn;
    }

    void MacWindow::enableVSync() {
        glfwSwapInterval( 1 );
        _data.vsync = true;
    }

    void MacWindow::disbaleVSync() {
        glfwSwapInterval( 0 );
        _data.vsync = false;
    }

    void MacWindow::createContext(const RendererBackend& backend) {
        switch (backend) {
            case RendererBackend::OpenGL: _context = CreateScoped<OpenGLContext>( _glfwWindow ); break;
            default: CORE_ASSERT( false, "Unsupported Backend" );
        }
        _context->init();
    }

    void MacWindow::shutdown() {
        glfwDestroyWindow( _glfwWindow );
        glfwTerminate();
    }

    void MacWindow::setCallbacks() {
        // cursor position callback
        glfwSetCursorPosCallback( _glfwWindow, [](GLFWwindow* window, double xpos, double ypos){
                windowData& data = *(windowData*)glfwGetWindowUserPointer( window );
                MouseMovedEvent event( (float)xpos, (float)ypos );
                data.callback( event );
        });

        // scroll callback
        glfwSetScrollCallback( _glfwWindow, [](GLFWwindow* window, double xoffset, double yoffset){
                windowData& data = *(windowData*)glfwGetWindowUserPointer( window );
                MouseScrolledEvent event( (float)xoffset, (float)yoffset );
                data.callback( event );
        });

        // mouse button callback
        glfwSetMouseButtonCallback( _glfwWindow, [](GLFWwindow* window, int button, int action, int mods){
                windowData& data = *(windowData*)glfwGetWindowUserPointer( window );
                switch (action) {
                    case GLFW_PRESS:
                    {
                        MouseButtonPressedEvent event( (MouseCode_t)button, (Mod_t)mods );
                        data.callback( event );
                        break;
                    }
                    case GLFW_RELEASE:
                    {
                        MouseButtonReleasedEvent event( (MouseCode_t)button, (Mod_t)mods );
                        data.callback( event );
                        break;
                    }
                }
        });

        // key callback
        glfwSetKeyCallback( _glfwWindow, [](GLFWwindow* window, int key, int scanecode, int action, int mods){
                windowData& data = *(windowData*)glfwGetWindowUserPointer( window );
                switch (action) {
                    case GLFW_PRESS:
                    {
                        KeyPressedEvent event( (KeyCode_t)key, (Mod_t)mods, false );
                        data.callback( event );
                        break;
                    }
                    case GLFW_REPEAT:
                    {
                        KeyPressedEvent event( (KeyCode_t)key, (Mod_t)mods, true );
                        data.callback( event );
                        break;
                    }
                    case GLFW_RELEASE:
                    {
                        KeyReleasedEvent event( (KeyCode_t)key, (Mod_t)mods );
                        data.callback( event );
                        break;
                    }
                    default: CORE_WARN( "caught unknown key" );
                }
        });

        // window resize callback
        glfwSetWindowSizeCallback( _glfwWindow, [](GLFWwindow* window, int width, int height){
            windowData& data = *(windowData*)glfwGetWindowUserPointer( window );
            data.width = width;
            data.height = height;
            WindowResizeEvent event( (uint32_t)width, (uint32_t)height );
            data.callback( event );
        });

        // window close callback
        glfwSetWindowCloseCallback( _glfwWindow, [](GLFWwindow* window){
            windowData& data = *(windowData*)glfwGetWindowUserPointer( window );
            WindowCloseEvent event;
            data.callback( event );
        });
    }
}
