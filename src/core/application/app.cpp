#include "core/application/app.h"
#include "core/application/appOpenGL.h"
#include "core/application/appMetal.h"
#include "core/renderer/renderer.h"
#include "editor/editorLayer.h"

#ifdef DEFAULT_CREATE_APP
Engine7414::App* Engine7414::appCreate(int argc, char** argv) {
    // TODO parser stuff, control verbosity here
    return new Engine7414::App;
}
#endif

namespace Engine7414
{
    // to make sure that only one application exists
    App* App::appInstancePtr = NULL;

    App::App(RendererBackend backend, const char* name, int verbosity) :
        _shouldRun(true),
        _minimized(false)
    {
        if ( appInstancePtr ) {
            CORE_ASSERT( false, "Application already exists! You cannot create another one!" );
        }
        else appInstancePtr = this;

        // initialize logger
        Log::init( verbosity );
        CORE_INFO( "Engine Initializing..." );

        // default window
        _window = Window::create({ name ? name : "Engine7414", 1280, 960, backend, true });
        _window->setEventCallback( CORE_BIND_EVENT_FN(App::onEvent) );

        // initialize renderer
        Renderer::init( backend );
        switch ( backend ) {
            case RendererBackend::OpenGL: _appBase = new AppOpenGL; break;
            case RendererBackend::Metal:  _appBase = new AppMetal; break;
            default: CORE_ASSERT( false, "" );
        }

        // ImGui layer
        this->pushOverlay( _imguiLayer = ImGuiLayer::create(backend) );
    }

    App::~App() {
        delete _appBase;
    }

    void App::run() {
        _appBase->run(*this);
    }

    void App::close() {
        appInstancePtr->_shouldRun = false;
    }

    void App::onEvent(Event& event) {
        EventDispatcher dispatcher( event );

        dispatcher.dispatch<WindowCloseEvent>( CORE_BIND_EVENT_FN(App::onWindowClose) );
        dispatcher.dispatch<WindowResizeEvent>( CORE_BIND_EVENT_FN(App::onWindowResize) );

        for (auto it = _layerStack.rbegin(); it != _layerStack.rend(); ++it) {
            if ( event.handled() ) break;
            (*it)->onEvent( event );
        }
    }

    void App::pushLayer(Layer* layer) {
        _layerStack.pushLayer( layer );
    }

    void App::pushOverlay(Layer* layer) {
        _layerStack.pushOverlay( layer );
    }

    bool App::onWindowClose(WindowCloseEvent& event) {
        _shouldRun = false;
        return true;
    }

    bool App::onWindowResize(WindowResizeEvent& event) {
        if (event.width() == 0 || event.height() == 0) {
            return (_minimized = true);
        }
        _minimized = false;
        Renderer::onWindowResize(event);
        return false;
    }

    bool App::onWindowIconify(WindowIconifyEvent& event) {
        CORE_INFO("{} called", __PRETTY_FUNCTION__);
        _minimized = true;
        return true;
    }
}
