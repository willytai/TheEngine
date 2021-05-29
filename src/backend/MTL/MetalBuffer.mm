#import "backend/MTL/MetalBuffer.h"

@implementation MTLVertexBufferHandle
- (instancetype) initWithSize:(NSUInteger)size From:(id<MTLDevice>)device {
    if ( (self = [super init]) ) {
        self.buffer = [device newBufferWithLength:size options:MTLResourceStorageModeManaged];
    }
    return self;
}

- (void)syncGPUWithCPU:(NSUInteger)size {
    NSRange range = {0, size}; // {<location>, <length>}
    [self.buffer didModifyRange:range];
}
@end

@implementation MTLIndexBufferHandle
- (instancetype) initWithBytes:(const void*)data Length:(NSUInteger)length From:(id<MTLDevice>)device {
    if ( (self = [super init]) ) {
        self.buffer = [device newBufferWithBytes:data length:length options:MTLResourceStorageModeManaged];
    }
    return self;
}
@end
