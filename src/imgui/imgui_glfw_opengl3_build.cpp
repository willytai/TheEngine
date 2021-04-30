#include "imconfig.h"

#if defined(__clang__)
    #pragma clang diagnostic push
    #pragma clang diagnostic ignored "-Wsign-conversion"
#elif defined(__GNUC__)
    #pragma GCC diagnostic push
    #pragma GCC diagnostic ignored "-Wsign-conversion"
#else
    #error "Compiler Not Supported!"
#endif

#include "imgui/backends/imgui_impl_opengl3.cpp"

#if defined(__clang__)
    #pragma clang diagnostic pop
#elif defined(__GNUC__)
    #pragma GCC diagnostic pop
    #error "Compiler Not Supported!"
#endif
