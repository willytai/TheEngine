#ifndef __APP_BASE_H__
#define __APP_BASE_H__

#include "core/application/app.h"

namespace Engine7414
{
    class AppBase
    {
    public:
        virtual ~AppBase() = default;
        virtual void run(App& app) = 0;
    };
}

#endif /* ifndef __APP_BASE_H__ */
