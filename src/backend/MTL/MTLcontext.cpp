#include "backend/MTL/MTLcontext.h"
#include "backend/backend.h"

#define GLFW_INCLUDE_NONE
#define GLFW_EXPOSE_NATIVE_COCOA
#include <GLFW/glfw3.h>
#include <GLFW/glfw3native.h>

namespace Engine7414
{
    MTLContext* MTLContext::__instance__ = NULL;

    GlobalContext* MTLContext::getContext() {
        return __instance__->_context;
    }

    MTLContext::MTLContext(GLFWwindow* handle) :
        _handle(handle),
        _context(nil)
    {
        if ( __instance__ ) BACKEND_ERROR( "You cannot create multiple context!" );
        else __instance__ = this;
    }

    void MTLContext::init() {
        _context = [[GlobalContext alloc] initWithCocoaWindow:glfwGetCocoaWindow(_handle)];

        BACKEND_VERIFY( _context.nativeDevice, "Device Not Found!" );
        BACKEND_INFO( "Metal Info" );
        BACKEND_INFO( "\tRenderer: {}", _context.nativeDevice.name.UTF8String );

    }

    void MTLContext::swapBuffers() {

    }

    // swap interval is not configurable on OS X
    void MTLContext::swapInterval(int interval) {

    }
}
