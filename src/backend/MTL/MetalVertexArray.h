#ifndef __MTL_VERTEX_ARRAY_OBJC_H__
#define __MTL_VERTEX_ARRAY_OBJC_H__

#import <Metal/Metal.h>

@interface MTLVertexArrayHandle : NSObject
@property (nonatomic, strong) MTLVertexDescriptor* vertexDescriptor;
- (instancetype) init;
- (void) setElementFormat:(MTLVertexFormat)format
              BufferIndex:(NSUInteger)index
                   Offset:(NSUInteger)offset;
- (void) setStride:(NSUInteger)stride;
@end

#endif /* ifndef __MTL_VERTEX_ARRAY_OBJC_H__ */
