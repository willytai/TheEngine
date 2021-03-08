#ifndef __CORE_H__
#define __CORE_H__

#include "config.h"
#include "util/log.h"
#include <signal.h>

#ifdef ENGINE_DEBUG
    #define CORE_ASSERT(x, msg) if (!(x)) { CORE_ERROR( msg ); raise(SIGTRAP); }
#else
    #define CORE_ASSERT(x, msg)
#endif

#define CORE_BIND_EVENT_FN(fn) std::bind(&fn, this, std::placeholders::_1)

#endif /* __CORE_H__ */
