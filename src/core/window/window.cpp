#include "core/window/window.h"
#include "core/input/input.h"
#include "core/core.h"
#include "platform/platform.h"

namespace Engine7414
{
    Scoped<Window> Window::create(const WindowProps& props) {
#ifdef __APPLE__
        return CreateScoped<MacWindow>( props );
#elif  _WIN64
        return CreateScoped<WindowsWindow>(props);
#else
    #error Engine7414 currently supports Mac and Windows(64-bit) only!
#endif
    }
}
