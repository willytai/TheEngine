#import "backend/MTL/MetalVertexArray.h"

@implementation MTLVertexArrayHandle
- (instancetype) init {
    if ( (self = [super init]) ) {
        self.vertexDescriptor = [[MTLVertexDescriptor alloc] init];
    }
    return self;
}

- (void) setElementFormat:(MTLVertexFormat)format BufferIndex:(NSUInteger)index Offset:(NSUInteger)offset {

}

- (void) setStride:(NSUInteger)stride {
    _vertexDescriptor.layouts[0].stride = stride;
    _vertexDescriptor.layouts[0].stepFunction = MTLVertexStepFunctionPerVertex;
}
@end
