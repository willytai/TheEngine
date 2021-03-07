#include "core/app.h"

#ifdef DEFAULT_CREATE_APP
Engine7414::App* Engine7414::appCreate(int argc, char** argv) {
    // TODO parser stuff, control verbosity here
    return new Engine7414::App;
}
#endif

namespace Engine7414
{
    App::App(int verbosity) :
        _shouldRun(true),
        _minimized(false)
    {
        util::Log::init( verbosity );
        CORE_INFO( "engine initializing" );
        _window = std::unique_ptr<Window>(Window::create( "Engine7414", 1280, 960, true ));
        _window->setEventCallback( CORE_BIND_EVENT_FN(App::onEvent) );
    }

    void App::run() {
        CORE_INFO( "engine started" );
        while ( _shouldRun ) {
            if ( !_minimized ) {
                // Everything else goes in here!!!
                for (auto& layer : _layerStack) {
                    layer->onUpdate();
                }
            }
            _window->onUpdate();
        }
        this->shutdown();
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

    bool App::onWindowClose(WindowCloseEvent& e) {
        _shouldRun = false;
        return true;
    }

    bool App::onWindowResize(WindowResizeEvent& e) {
        _minimized = false;
        return false;
    }

    bool App::onWindowIconify(WindowIconifyEvent& e) {
        _minimized = true;
        return false;
    }

    void App::shutdown() {
        glfwTerminate();
    }
}
