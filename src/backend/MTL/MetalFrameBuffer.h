#ifndef __MTL_FRAME_BUFFER_OBJC_H__
#define __MTL_FRAME_BUFFER_OBJC_H__

#import <Metal/Metal.h>

// @class MTLFrameBufferHandle;
// 
// @interface MTLFrameBufferKey : NSObject<NSCopying>
// @property (nonatomic, assign) u_int32_t sampleCount;
// @property (nonatomic, assign) MTLPixelFormat colorPixelFormat;
// @property (nonatomic, assign) MTLPixelFormat depthPixelFormat;
// @property (nonatomic, assign) MTLPixelFormat stencilPixelFormat;
// - (instancetype)initWithHandle:(MTLFrameBufferHandle*)handle;
// @end

// TODO
// not sure how to free the resource when framebuffer is resized
// assuming the texture is being freed once the ref count reaches 0
@interface MTLFrameBufferHandle : NSObject
// @property (nonatomic, strong) MTLFrameBufferKey* cacheKey;
@property (nonatomic, strong) MTLTextureDescriptor* colorAttachmentDiscriptor;
@property (nonatomic, strong) MTLTextureDescriptor* depthAttachmentDiscriptor;
@property (nonatomic, strong) id<MTLTexture> colorAttachment;
@property (nonatomic, strong) id<MTLTexture> depthAttachment;
@property (nonatomic, strong) id<MTLSamplerState> sampler;
- (instancetype) initWithDimensionWidth:(uint32_t)width Height:(uint32_t)height Device:(id<MTLDevice>)device;
- (void) reGenWithDimensionWidth:(uint32_t)width Height:(uint32_t)height Device:(id<MTLDevice>)device;
@end


#endif /* ifndef __MTL_FRAME_BUFFER_OBJC_H__ */
