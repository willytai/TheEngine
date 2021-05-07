#import "backend/MTL/MTLrenderAPI.h"

#include "core/core.h"
#include "core/renderer/renderer.h"

#include "core/application/app.h"
#include "backend/MTL/MTLcontext.h"

@implementation MTLRenderPipelineStateKey
- (instancetype)init {
    if ( (self = [super init]) ) {
        _vertexFunc = nil;
        _fragmentFunc = nil;
    }
    return self;
}

- (nonnull id)copyWithZone:(nullable NSZone *)zone
{
    MTLRenderPipelineStateKey* copy = [[MTLRenderPipelineStateKey allocWithZone:zone] init];
    copy.sampleCount = self.sampleCount;
    copy.colorPixelFormat = self.colorPixelFormat;
    copy.depthPixelFormat = self.depthPixelFormat;
    copy.stencilPixelFormat = self.stencilPixelFormat;
    copy.vertexFunc = self.vertexFunc;
    copy.fragmentFunc = self.fragmentFunc;
    return copy;
}
// - (NSUInteger)hash
// {
//     NSUInteger sc = _sampleCount & 0x3;
//     NSUInteger cf = _colorPixelFormat & 0x3FF;
//     NSUInteger df = _depthPixelFormat & 0x3FF;
//     NSUInteger sf = _stencilPixelFormat & 0x3FF;
//     NSUInteger hash = (sf << 22) | (df << 12) | (cf << 2) | sc;
//     return hash;
// }
- (BOOL)isEqual:(id)object
{
    MTLRenderPipelineStateKey* other = object;
    if (![other isKindOfClass:[MTLRenderPipelineStateKey class]])
        return NO;
    return other.sampleCount == self.sampleCount        &&
    other.colorPixelFormat   == self.colorPixelFormat   &&
    other.depthPixelFormat   == self.depthPixelFormat   &&
    other.stencilPixelFormat == self.stencilPixelFormat &&
    other.fragmentFunc       == self.fragmentFunc       &&
    other.vertexFunc         == self.vertexFunc;
}
@end

@implementation MTLRenderHandle
- (instancetype)init {
    if ( (self = [super init]) ) {
        self.renderPassDescriptor = [[MTLRenderPassDescriptor alloc] init];
        self.renderPassDescriptor.colorAttachments[0].loadAction = MTLLoadActionClear;
        self.renderPassDescriptor.colorAttachments[0].storeAction = MTLStoreActionDontCare;

        // enable depth test
        self.renderPassDescriptor.depthAttachment.clearDepth = 1.0;

        self.rpsCacheKey = [[MTLRenderPipelineStateKey alloc] init];
        self.renderPipelineStateCache = [NSMutableDictionary dictionary];
        self.commandBuffer = nil;
        self.commandEncoder = nil;
        self.drawable = nil;
    }
    return self;
}
- (void)setClearColorR:(float)red G:(float)green B:(float)blue A:(float)alpha {
    _renderPassDescriptor.colorAttachments[0].clearColor = MTLClearColorMake( red, green, blue, alpha );
}
- (void)setClear {
    _renderPassDescriptor.colorAttachments[0].loadAction = MTLLoadActionClear;
}
- (void)begin {
    // new drawable
    // int width, height;
    // glfwGetFramebufferSize( (GLFWwindow*)Engine7414::App::getWindow()->nativeWindow(), &width, &height );
    // context.swapChain.drawableSize = CGSizeMake( width, height );
    // _drawable = [context.swapChain nextDrawable];

    // set to renderPassDescriptor
    // _renderPassDescriptor.colorAttachments[0].texture = _drawable.texture;

    // new buffer and encoder
    GlobalContext* context = Engine7414::MTLContext::getContext();
    _commandBuffer = [context.commandQueue commandBuffer];
    _commandEncoder = [_commandBuffer renderCommandEncoderWithDescriptor:_renderPassDescriptor];

    // set the correct pipeline state
    id<MTLRenderPipelineState> state = [self getRenderPipelineState_];
    [_commandEncoder setRenderPipelineState:state];

    // realease the cache key
    // self.rpsCacheKey = nil;
}
- (void)end {
    [_commandEncoder endEncoding];
    // [_commandBuffer presentDrawable:_drawable];
    [_commandBuffer commit];
}
- (id<MTLRenderPipelineState>)getRenderPipelineState_ {
    assert(self.rpsCacheKey);
    id<MTLRenderPipelineState> state = self.renderPipelineStateCache[self.rpsCacheKey];

    if ( state == nil ) {
        state = [self newRenderPipelineState_];
        self.renderPipelineStateCache[self.rpsCacheKey] = state;
    }

    return state;
}
- (id<MTLRenderPipelineState>)newRenderPipelineState_ {
    auto* context = Engine7414::MTLContext::getContext();
    MTLRenderPipelineDescriptor* decs = [[MTLRenderPipelineDescriptor alloc] init];
    decs.colorAttachments[0].pixelFormat = self.rpsCacheKey.colorPixelFormat;
    decs.depthAttachmentPixelFormat = self.rpsCacheKey.depthPixelFormat;
    decs.stencilAttachmentPixelFormat = self.rpsCacheKey.stencilPixelFormat;
    decs.sampleCount = self.rpsCacheKey.sampleCount;
    decs.vertexFunction = self.rpsCacheKey.vertexFunc;
    decs.fragmentFunction = self.rpsCacheKey.fragmentFunc;

    // TODO this is temporary
    MTLVertexDescriptor* vd = [[MTLVertexDescriptor alloc] init];
    vd.attributes[0].format = MTLVertexFormatFloat3;
    vd.attributes[0].bufferIndex = 0;
    vd.attributes[0].offset = 0;
    vd.attributes[1].format = MTLVertexFormatFloat4;
    vd.attributes[1].bufferIndex = 0;
    vd.attributes[1].offset = 3 * sizeof(float);
    vd.attributes[2].format = MTLVertexFormatFloat2;
    vd.attributes[2].bufferIndex = 0;
    vd.attributes[2].offset = 7 * sizeof(float);
    vd.attributes[3].format = MTLVertexFormatInt;
    vd.attributes[3].bufferIndex = 0;
    vd.attributes[3].offset = 9 * sizeof(float);
    vd.layouts[0].stride = 9 * sizeof(float) + sizeof(int);
    vd.layouts[0].stepFunction = MTLVertexStepFunctionPerVertex;
    decs.vertexDescriptor = vd;

    NSError* error;
    id<MTLRenderPipelineState> state = [context.nativeDevice newRenderPipelineStateWithDescriptor:decs error:&error];
    if (error != nil)
    {
         NSLog(@"Error: failed to create Metal pipeline state: %@", error);
         assert(false);
    }
    else assert(state);
    return state;
}
@end

namespace Engine7414
{
    MTLRenderAPI* MTLRenderAPI::__instance__ = NULL;

    MTLRenderAPI::MTLRenderAPI() {
        if ( __instance__ ) {
            BACKEND_ASSERT( false, "multiple render API not supported" );
        }
        _handle = [[MTLRenderHandle alloc] init];
        __instance__ = this;
    }

    void MTLRenderAPI::init() const {
        // TODO
        // hard coding this for now, don't know the API to retrieve the information at runtime
        Renderer::setMaxTextSlot( 16 );
    }

    void MTLRenderAPI::setClearColor(const glm::vec4& color) const {
        [_handle setClearColorR:color.r G:color.g B:color.b A:color.a];
    }

    void MTLRenderAPI::clear() const {
        [_handle setClear];
    }

    void MTLRenderAPI::begin() const {
        [_handle begin];
    }

    void MTLRenderAPI::end() const {
        [_handle end];
    }

    void MTLRenderAPI::drawElement(const Ref<VertexArray>& vertexArray, const uint32_t& indexCount) const {
    }

    void MTLRenderAPI::setViewPort(const uint32_t& x, const uint32_t& y, const uint32_t& width, const uint32_t& height) const {
    }

}
