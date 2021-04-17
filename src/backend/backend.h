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

// enabled for debug and release build
// a soft check, doesn't abort the program
#define BACKEND_VERIFY(x, ...) if ( !(x) ) { CORE_WARN( __VA_ARGS__); }

#define STRINGIFY(str) #str

namespace Engine7414
{
    enum class RendererBackend : uint8_t
    {
        None,
        OpenGL,
        Metal
    };
}

#endif /* __BACKEND_H__ */
