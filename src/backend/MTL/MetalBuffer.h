#ifndef __MTL_BUFFER_OBJC_H__
#define __MTL_BUFFER_OBJC_H__

#import <Metal/Metal.h>

@interface MTLVertexBufferHandle : NSObject
@property (nonatomic, strong) id<MTLBuffer> buffer;
- (instancetype) initWithSize:(NSUInteger)size From:(id<MTLDevice>)device;
- (void)syncGPUWithCPU:(NSUInteger)size;
@end

@interface MTLIndexBufferHandle : NSObject
@property (nonatomic, strong) id<MTLBuffer> buffer;
- (instancetype) initWithBytes:(const void*)data Length:(NSUInteger)length From:(id<MTLDevice>)device;
@end

#endif /* ifndef __MTL_BUFFER_OBJC_H__ */
