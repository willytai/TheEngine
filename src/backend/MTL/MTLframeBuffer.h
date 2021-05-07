#ifndef __MTL_FRAME_BUFFER_H__
#define __MTL_FRAME_BUFFER_H__

#include "core/renderer/frameBuffer.h"

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
- (instancetype) initWithDimensionWidth:(uint32_t)width Height:(uint32_t)height;
- (void) reGenWithDimensionWidth:(uint32_t)width Height:(uint32_t)height;
@end

namespace Engine7414
{
    class MTLFrameBuffer : public FrameBuffer
    {
    public:
        MTLFrameBuffer(const FrameBufferSpec& spec);
        ~MTLFrameBuffer();

        void bind() const override;
        void unbind() const override;
        void resize(const uint32_t& width, const uint32_t& height) override;
        void* colorAttachmentID() const override;
        const FrameBufferSpec& spec() const override { return _spec; }

    private:
        void regenerate();

    private:
        MTLFrameBufferHandle* _handle;

        FrameBufferSpec  _spec;
    };
}

#endif /* __MTL_FRAME_BUFFER_H__ */
