#include "core/window/window.h"
#include "core/input/input.h"
#include "core/core.h"

#ifdef __APPLE__
    #include "platform/Mac/macWindow.h"
#else
    #error Engine7414 currently supports Mac only!
#endif

namespace Engine7414
{
    Scoped<Window> Window::create(const WindowProps& props) {
#ifdef __APPLE__
        return CreateScoped<MacWindow>( props );
#else
    #error Engine7414 currently supports Mac only!
#endif
    }
}
