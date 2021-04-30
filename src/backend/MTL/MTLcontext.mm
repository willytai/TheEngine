#include "backend/MTL/MTLcontext.h"
#include "backend/backend.h"

#define GLFW_INCLUDE_NONE
#define GLFW_EXPOSE_NATIVE_COCOA
#include <GLFW/glfw3.h>
#include <GLFW/glfw3native.h>

namespace Engine7414
{
    MetalContext::MetalContext(GLFWwindow* handle) :
        _handle(handle) {}

    void MetalContext::init() {
        _device = MTLCreateSystemDefaultDevice();
        BACKEND_VERIFY( _device, "Device Not Found!" );
        BACKEND_INFO( "Metal Info" );
        BACKEND_INFO( "\tRenderer: {}", _device.name.UTF8String );

        // swap chain
        CAMetalLayer* swapChain = [CAMetalLayer layer];
        swapChain.device = _device;
        swapChain.opaque = YES;
        swapChain.pixelFormat = MTLPixelFormatBGRA8Unorm;

        // native window
        NSWindow* nswin = glfwGetCocoaWindow( _handle );
        nswin.contentView.layer = swapChain;
        nswin.contentView.wantsLayer = YES;

        // command queue (not a light weight object, should be reused)
        id<MTLCommandQueue> CommandQ = [_device newCommandQueue];
    }

    void MetalContext::swapBuffers() {

    }

    // swap interval is not configurable on OS X
    void MetalContext::swapInterval(int interval) {

    }

    id<MTLDevice> MetalContext::device() {
        return _device;
    }
}
