#include "core/core.h"
#include "core/event/event.h"
#include "core/input/input.h"
#include "core/util/log.h"
#include "backend/OpenGL/GLcontext.h"
#include "platform/Mac/macWindow.h"
#include "glad/glad.h"

namespace Engine7414
{
    Window* Window::create(const char* title, int width, int height, const RendererBackend& backend, bool vsync) {
        MacWindow* window = new MacWindow( title, width, height, backend );
        if ( vsync ) window->enableVSync();
        else         window->disbaleVSync();
        Input::bindWindow( window );
        return window;
    }

    bool MacWindow::__glfwInitialized__ = false;

    MacWindow::MacWindow(const char* title, int width, int height, const RendererBackend& backend) :
        Window( title ),
        _glfwWindow(NULL)
    {
        _data.width = width;
        _data.height = height;

        if ( !__glfwInitialized__ ) {
            if ( glfwInit() ) {
                glfwWindowHint( GLFW_CONTEXT_VERSION_MAJOR, 4 );
                glfwWindowHint( GLFW_CONTEXT_VERSION_MINOR, 1 );
                glfwWindowHint( GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE );
                glfwWindowHint( GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE );
            }
            else {
                GLFW_ERROR( "glfw falied to initialize!" );
                CORE_ASSERT( false, "error not yet handled, aborting..." );
            }
            __glfwInitialized__ = true;
        }

        if ( (_glfwWindow = glfwCreateWindow( width, height, title, NULL, NULL )) == NULL ) {
            GLFW_ERROR( "unable to create window!" );
            CORE_ASSERT( false, "glfw failed to create window, error not yet handled, aborting..." );
        }

        glfwSetInputMode( _glfwWindow, GLFW_LOCK_KEY_MODS, GLFW_TRUE ); // enable modifier key flags
        glfwSetWindowUserPointer( _glfwWindow, &_data );
        this->createContext( backend );
        this->enableVSync();

        CORE_INFO( "window \'{}\' successfully created ({}, {})", title, width, height );

        // GLFW callbacks
        this->setCallbacks();
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
            case RendererBackend::OpenGL: _context = new OpenGLContext( _glfwWindow ); break;
            default: CORE_ASSERT( false, "Unsupported Backend" );
        }
        _context->init();
    }

    void MacWindow::shutdown() {
        glfwDestroyWindow( _glfwWindow );
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
                        MouseButtonPressedEvent event( button, mods );
                        data.callback( event );
                        break;
                    }
                    case GLFW_RELEASE:
                    {
                        MouseButtonReleasedEvent event( button, mods );
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
                        KeyPressedEvent event( key, mods, false );
                        data.callback( event );
                        break;
                    }
                    case GLFW_REPEAT:
                    {
                        KeyPressedEvent event( key, mods, true );
                        data.callback( event );
                        break;
                    }
                    case GLFW_RELEASE:
                    {
                        KeyReleasedEvent event( key, mods );
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
            WindowResizeEvent event( width, height );
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
