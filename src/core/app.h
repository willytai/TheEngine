#ifndef __APP_H__
#define __APP_H__

#include "core/core.h"
#include "core/window.h"
#include "core/event/event.h"
#include "util/log.h"
#include "platform/platform.h"
#include <memory>

namespace Engine7414
{
    class App
    {
    public:
        App(int verbosity = -1);
        virtual ~App() {}

        void run();
        void onEvent(Event& event);

    private:
        bool _shouldRun;
        std::unique_ptr<Window> _window;
    };

    App* appCreate(int argc, char** argv);
}

#endif /* __APP_H__ */
