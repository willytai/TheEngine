#ifndef __BACKEND_H__
#define __BACKEND_H__

#include "util/log.h"
#include <signal.h>

#ifdef ENGINE_DEBUG
    #define BACKEND_ASSERT(x, msg) if (!(x)) { BACKEND_ERROR( msg ); raise(SIGTRAP); }
#else
    #define BACKEND_ASSERT(x, msg)
#endif

#endif /* __BACKEND_H__ */
