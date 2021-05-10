#ifndef __MTL_CONTEXT_OBJC_H__
#define __MTL_CONTEXT_OBJC_H__

#import <Metal/Metal.h>
#import <QuartzCore/QuartzCore.h>
#import <Cocoa/Cocoa.h>

@interface GlobalContext : NSObject
@property (nonatomic, strong) id<MTLDevice> nativeDevice;
@property (nonatomic, strong) id<MTLCommandQueue> commandQueue;
@property (nonatomic, strong) CAMetalLayer* swapChain;
- (instancetype) initWithCocoaWindow:(NSWindow*)nsWindow;
@end

#endif /* ifndef __MTL_CONTEXT_OBJC_H__ */
