#ifndef __BACKEND_H__
#define __BACKEND_H__

#include "core/util/log.h"
#include <signal.h>

#ifdef ENGINE_DEBUG
    #define BACKEND_ASSERT(x, ...) if (!(x)) { BACKEND_ERROR( __VA_ARGS__ ); raise(SIGTRAP); }
#else
    #define BACKEND_ASSERT(x, msg)
#endif

#define STRINGIFY(str) #str

namespace Engine7414
{
    enum class RendererBackend : uint8_t
    {
        None,
        OpenGL
    };
}

#endif /* __BACKEND_H__ */
