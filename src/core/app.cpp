#include "core/app.h"

#ifdef DEFAULT_CREATE
engine7414::App* engine7414::appCreate(int argc, char** argv) {
    // TODO parser stuff, control verbosity here
    return new engine7414::App;
}
#endif

namespace engine7414
{
    App::App(int verbosity) {
        util::Log::init( verbosity );
    }

    void App::run() {
        CORE_INFO( "engine started" );
        while (true);
    }
}
