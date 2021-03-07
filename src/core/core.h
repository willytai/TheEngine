#ifndef __CORE_H__
#define __CORE_H__

#ifndef ENGINE_BACKEND_OPENGL
    #error Engine7414 only supports OpenGL backend currently!
#endif

#include "util/log.h"
#include <cassert>

#ifdef ENGINE_DEBUG
    #define CORE_ASSERT(x, msg) if (!(x)) { CORE_ERROR( msg ); assert(false); }
#else
    #define CORE_ASSERT(x, msg)
#endif

#define CORE_BIND_EVENT_FN(fn) std::bind(&fn, this, std::placeholders::_1)

#endif /* __CORE_H__ */
