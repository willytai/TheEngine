#include "backend/MTL/MTLcontext.h"
#include "backend/backend.h"

#define GLFW_INCLUDE_NONE
#define GLFW_EXPOSE_NATIVE_COCOA
#include <GLFW/glfw3.h>
#include <GLFW/glfw3native.h>

// objective c/c++ class
@implementation GlobalContext
- (instancetype)init {
    if ( (self = [super init]) ) {
        self.nativeDevice = MTLCreateSystemDefaultDevice();
        self.commandQueue = [self.nativeDevice newCommandQueue];

        // swap chain
        self.swapChain = [CAMetalLayer layer];
        self.swapChain.device = self.nativeDevice;
        self.swapChain.opaque = YES;
        self.swapChain.pixelFormat = MTLPixelFormatBGRA8Unorm;
    }
    return self;
}
@end

namespace Engine7414
{
    MetalContext* MetalContext::__instance__ = NULL;

    GlobalContext* MetalContext::getContext() {
        return __instance__->_context;
    }

    MetalContext::MetalContext(GLFWwindow* handle) :
        _handle(handle),
        _context(nil)
    {
        if ( __instance__ ) BACKEND_ERROR( "You cannot create multiple context!" );
        else __instance__ = this;
    }

    void MetalContext::init() {
        _context = [[GlobalContext alloc] init];

        BACKEND_VERIFY( _context.nativeDevice, "Device Not Found!" );
        BACKEND_INFO( "Metal Info" );
        BACKEND_INFO( "\tRenderer: {}", _context.nativeDevice.name.UTF8String );


        // native window
        NSWindow* nswin = glfwGetCocoaWindow( _handle );
        nswin.contentView.layer = _context.swapChain;
        nswin.contentView.wantsLayer = YES;
    }

    void MetalContext::swapBuffers() {

    }

    // swap interval is not configurable on OS X
    void MetalContext::swapInterval(int interval) {

    }
}
