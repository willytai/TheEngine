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
