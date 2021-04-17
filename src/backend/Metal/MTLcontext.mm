#include "backend/Metal/MTLcontext.h"
#include "backend/backend.h"

#import <Metal/Metal.h>
#import <QuartzCore/QuartzCore.h>

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

    void* MetalContext::device() {
        // TODO not sure if this is correct
        return (__bridge void*)_device;
    }
}
