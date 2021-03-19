#ifndef __BACKEND_H__
#define __BACKEND_H__

#include "core/util/log.h"

#ifdef ENGINE_DEBUG
    #ifdef _WIN64
        #define BACKEND_ASSERT(x, ...) if (!(x)) { CORE_ERROR( __VA_ARGS__ ); __debugbreak(); }
    #else
        #include <signal.h>
        #define BACKEND_ASSERT(x, ...) if (!(x)) { CORE_ERROR( __VA_ARGS__ ); raise(SIGTRAP); }
    #endif
#else
    #define BACKEND_ASSERT(x, ...)
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
