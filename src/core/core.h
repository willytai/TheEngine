#ifndef __CORE_H__
#define __CORE_H__

#include "config.h"
#include "util/log.h"
#include <memory>

#ifdef _MSC_VER
    #define __PRETTY_FUNCTION__ __FUNCSIG__
#endif

#ifdef ENGINE_DEBUG
    #ifdef _WIN64
        #define CORE_ASSERT(x, ...) if (!(x)) { CORE_ERROR( __VA_ARGS__ ); CORE_FATAL( "In {}, {}:{}", __PRETTY_FUNCTION__, __FILE__, __LINE__ ); __debugbreak(); }
        #define CORE_VERIFY(x, ...) if (!(x)) { CORE_ERROR( __VA_ARGS__ ); CORE_FATAL( "In {}, {}:{}", __PRETTY_FUNCTION__, __FILE__, __LINE__ ); __debugbreak(); }
    #else
        #include <signal.h>
        #define CORE_ASSERT(x, ...) if (!(x)) { CORE_ERROR( __VA_ARGS__ ); CORE_FATAL( "In {}, {}:{}", __PRETTY_FUNCTION__, __FILE__, __LINE__ ); raise(SIGTRAP); }
        #define CORE_VERIFY(x, ...) if (!(x)) { CORE_ERROR( __VA_ARGS__ ); CORE_FATAL( "In {}, {}:{}", __PRETTY_FUNCTION__, __FILE__, __LINE__ ); raise(SIGTRAP); }
    #endif
#else
    #define CORE_ASSERT(x, ...)
    #define CORE_VERIFY(x, ...) x
#endif

#define BUF_MAX 128

#define CORE_BIND_EVENT_FN(fn) std::bind(&fn, this, std::placeholders::_1)
#define CLIP_BETWEEN(target, minValue, maxValue) target = std::max(target, minValue); \
                                                 target = std::min(target, maxValue)
namespace Engine7414
{
    template <typename T>
    using Ref = std::shared_ptr<T>;

    // constexpr makes it inline
    template<typename T, typename ... Args>
    constexpr Ref<T> CreateRef(Args&& ... args) {
        return std::make_shared<T>(std::forward<Args>(args)...);
    }

    template <typename T>
    using Scoped = std::unique_ptr<T>;

    // constexpr makes it inline
    template<typename T, typename ... Args>
    constexpr Scoped<T> CreateScoped(Args&& ... args) {
        return std::make_unique<T>(std::forward<Args>(args)...);
    }
}

#endif /* __CORE_H__ */
