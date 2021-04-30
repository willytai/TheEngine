#include "imconfig.h"

#if defined(__clang__)
    #pragma clang diagnostic push
    #pragma clang diagnostic ignored "-Wnullability-completeness"
#elif defined(__GNUC__)
    #pragma GCC diagnostic push
    #pragma GCC diagnostic ignored "-Wnullability-completeness"
#else
    #error "Compiler Not Supported!"
#endif

#include "imgui/backends/imgui_impl_metal.mm"

#if defined(__clang__)
    #pragma clang diagnostic pop
#elif defined(__GNUC__)
    #pragma GCC diagnostic pop
    #error "Compiler Not Supported!"
#endif
