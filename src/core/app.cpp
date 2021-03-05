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
        _shouldRun(true)
    {
        util::Log::init( verbosity );
        CORE_INFO( "engine initializing" );
        _window = std::unique_ptr<Window>(Window::create( "Engine7414", 1280, 960, true ));
        _window->setEventCallback( std::bind(&App::onEvent, this, std::placeholders::_1) );
    }

    void App::run() {
        CORE_INFO( "engine started" );
        while ( _shouldRun ) {
            _window->onUpdate();
        }
    }

    void App::onEvent(Event& event) {
        std::cout << event << std::endl;
    }
}
