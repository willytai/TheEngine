#ifndef __MTL_RENDER_H__
#define __MTL_RENDER_H__

#import <Metal/Metal.h>
#import "backend/MTL/MTLcontext.h"
#import "backend/MTL/MTLframeBuffer.h"

#include "core/renderer/renderAPI.h"

// TODO not sure if strong or weak is better
@interface MTLRenderPipelineStateKey : NSObject<NSCopying>
@property (nonatomic, assign) u_int32_t sampleCount;
@property (nonatomic, assign) MTLPixelFormat colorPixelFormat;
@property (nonatomic, assign) MTLPixelFormat depthPixelFormat;
@property (nonatomic, assign) MTLPixelFormat stencilPixelFormat;
@property (nonatomic, strong) id<MTLFunction> vertexFunc;
@property (nonatomic, strong) id<MTLFunction> fragmentFunc;
- (instancetype)init;
@end

// need a renderPipelineState (maybe create key value pairs with framebuffers)?
@interface MTLRenderHandle : NSObject
@property (nonatomic, strong) MTLRenderPassDescriptor* renderPassDescriptor;
@property (nonatomic, strong) MTLRenderPipelineStateKey* rpsCacheKey;
@property (nonatomic, strong) NSMutableDictionary* renderPipelineStateCache;
@property (nonatomic, strong) id<MTLCommandBuffer> commandBuffer;
@property (nonatomic, strong) id<MTLRenderCommandEncoder> commandEncoder;
@property (nonatomic, strong) id<CAMetalDrawable> drawable;
- (void)setClearColorR:(float)red
                     G:(float)green
                     B:(float)blue
                     A:(float)alpha;
- (void)setClear;
- (void)begin;
- (void)end;
- (id<MTLRenderPipelineState>)getRenderPipelineState_;
- (id<MTLRenderPipelineState>)newRenderPipelineState_;
@end

namespace Engine7414
{
    class MTLRenderAPI : public RenderAPI
    {
        static MTLRenderAPI* __instance__;
    public:
        static MTLRenderHandle* getRenderHandle() { return __instance__->_handle; }

    public:
        MTLRenderAPI();
        ~MTLRenderAPI() {}
        void init() const override;
        void clear() const override;
        void setClearColor(const glm::vec4& color) const override;
        void drawElement(const Ref<VertexArray>& vertexArray, const uint32_t& indexCount = 0) const override;
        void setViewPort(const uint32_t& x, const uint32_t& y, const uint32_t& width, const uint32_t& height) const override;


        void begin() const override;
        void end() const override;

        RendererBackend backend() const override { return RendererBackend::Metal; }

    private:
        MTLRenderHandle* _handle = nil;
    };
}

#endif /* __MTL_RENDER_H__ */
