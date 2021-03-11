#ifndef __CORE_H__
#define __CORE_H__

#include "config.h"
#include "util/log.h"
#include <signal.h>

#ifdef ENGINE_DEBUG
    #define CORE_ASSERT(x, ...) if (!(x)) { CORE_ERROR( __VA_ARGS__ ); raise(SIGTRAP); }
#else
    #define CORE_ASSERT(x, msg)
#endif

#define CORE_BIND_EVENT_FN(fn) std::bind(&fn, this, std::placeholders::_1)

#endif /* __CORE_H__ */
