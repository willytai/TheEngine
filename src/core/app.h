#ifndef __APP_H__
#define __APP_H__

#include "core/config.h"
#include "util/log.h"

namespace engine7414
{
    class App
    {
    public:
        App(int verbosity = -1);
        virtual ~App() {}

        void run();
    };

    App* appCreate(int argc, char** argv);
}

#endif /* __APP_H__ */
