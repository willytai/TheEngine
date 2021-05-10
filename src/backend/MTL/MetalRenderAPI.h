#ifndef __MTL_RENDER_OBJC_H__
#define __MTL_RENDER_OBJC_H__

#import <Metal/Metal.h>
#import "backend/MTL/MTLcontext.h"

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
- (void)beginWithContext:(GlobalContext*)context;
- (void)end;
- (id<MTLRenderPipelineState>)getRenderPipelineStateFromContext_:(GlobalContext*)context;
- (id<MTLRenderPipelineState>)newRenderPipelineStateFromContext_:(GlobalContext*)context;
@end

#endif /* ifndef __MTL_RENDER_OBJC_H__ */
