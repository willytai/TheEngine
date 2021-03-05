#ifndef __CORE_H__
#define __CORE_H__

#include "util/log.h"
#include <cassert>

#define DEFAULT_CREATE_APP

#ifdef ENGINE_DEBUG
    #define CORE_ASSERT(x, msg) if (!(x)) { CORE_ERROR( msg ); assert(false); }
#else
    #define CORE_ASSERT(x, msg)
#endif

#endif /* __CORE_H__ */
