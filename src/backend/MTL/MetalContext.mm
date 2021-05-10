#import "backend/MTL/MetalContext.h"

@implementation GlobalContext
- (instancetype)initWithCocoaWindow:(NSWindow*)nsWindow {
    if ( (self = [super init]) ) {
        self.nativeDevice = MTLCreateSystemDefaultDevice();
        self.commandQueue = [self.nativeDevice newCommandQueue];

        // swap chain
        self.swapChain = [CAMetalLayer layer];
        self.swapChain.device = self.nativeDevice;
        self.swapChain.opaque = YES;
        self.swapChain.pixelFormat = MTLPixelFormatBGRA8Unorm;

        // native window
        nsWindow.contentView.layer = self.swapChain;
        nsWindow.contentView.wantsLayer = YES;
    }
    return self;
}
@end
