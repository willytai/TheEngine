#if defined(__clang__)
    #pragma clang diagnostic push
    #pragma clang diagnostic ignored "-Wconversion"
    #pragma clang diagnostic ignored "-Wsign-compare"
#elif defined(__GNUC__)
    #pragma GCC diagnostic push
    #pragma GCC diagnostic ignored "-Wconversion"
    #pragma GCC diagnostic ignored "-Wsign-compare"
#elif defined(_MSC_VER)
    #pragma warning(push)
#else
    #error "Compiler Not Supported!"
#endif

#define STB_IMAGE_IMPLEMENTATION
#include <stb/stb_image.h>

#if defined(__clang__)
    #pragma clang diagnostic pop
#elif defined(__GNUC__)
    #pragma GCC diagnostic pop
#elif defined(_MSC_VER)
    #pragma warning(pop)
#else
    #error "Compiler Not Supported!"
#endif
