#import "backend/MTL/MetalRenderAPI.h"

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
        // self.drawable = nil;

        // initialize cache
        // [NOTE] at most 16 textures are allowed
        self.textureCache = [NSMutableArray arrayWithCapacity:16];
        for (NSUInteger i = 0; i < 16; ++i) {
            [self.textureCache addObject:[NSNull null]];
        }
        self.shaderUniformBufferCache = nil;
    }
    return self;
}
- (void)setClearColorR:(float)red G:(float)green B:(float)blue A:(float)alpha {
    _renderPassDescriptor.colorAttachments[0].clearColor = MTLClearColorMake( red, green, blue, alpha );
}
- (void)setClear {
    _renderPassDescriptor.colorAttachments[0].loadAction = MTLLoadActionClear;
}
- (void)beginWithContext:(GlobalContext*)context {
    // new drawable
    // int width, height;
    // glfwGetFramebufferSize( (GLFWwindow*)Engine7414::App::getWindow()->nativeWindow(), &width, &height );
    // context.swapChain.drawableSize = CGSizeMake( width, height );
    // _drawable = [context.swapChain nextDrawable];

    // set to renderPassDescriptor
    // _renderPassDescriptor.colorAttachments[0].texture = _drawable.texture;

    // new buffer and encoder
    _commandBuffer = [context.commandQueue commandBuffer];
    _commandEncoder = [_commandBuffer renderCommandEncoderWithDescriptor:_renderPassDescriptor];

    // set the correct pipeline state
    id<MTLRenderPipelineState> state = [self getRenderPipelineStateFromContext_:context];
    [_commandEncoder setRenderPipelineState:state];

    // bind the static resource
    [self bindStaticResources_];

    // realease the cache key
    // self.rpsCacheKey = nil;
}
- (void)end {
    [_commandEncoder endEncoding];
    // [_commandBuffer presentDrawable:_drawable];
    [_commandBuffer commit];

    // reset
    _commandEncoder = nil;
    _commandBuffer = nil;
}
 
// [NOTE] textures are visible to the fragment shader for now
- (void)bindTexture:(id<MTLTexture>)texture toSlot:(NSUInteger)slot {
    if ( _commandEncoder == nil ) { // binding before render pass starts
        [_textureCache replaceObjectAtIndex:slot
                                 withObject:texture];
    }
    else {
        [_commandEncoder setFragmentTexture:texture
                                    atIndex:slot];
    }
}

- (void)bindUniformBuffer:(id<MTLBuffer>)buffer {
    if ( _commandEncoder == nil ) {
        _shaderUniformBufferCache = buffer;
    }
    else {
        [_commandEncoder setVertexBuffer:buffer
                                  offset:0
                                 atIndex:1];
        [_commandEncoder setFragmentBuffer:buffer
                                  offset:0
                                 atIndex:1];
    }
}

- (void)drawIndexed:(id<MTLBuffer>)dataBuffer
            indices:(id<MTLBuffer>)indexBuffer
          indexType:(MTLIndexType)indexType
         indexCount:(NSUInteger)indexCount
{
    [_commandEncoder setVertexBuffer:dataBuffer offset:0 atIndex:0];
    [_commandEncoder drawIndexedPrimitives:MTLPrimitiveTypeTriangle
                                indexCount:indexCount
                                 indexType:indexType
                               indexBuffer:indexBuffer
                         indexBufferOffset:0];
}

- (void) bindStaticResources_ {
    // set texture
    for (NSUInteger i = 0; i < _textureCache.count; ++i) {
        if ( _textureCache[i] != [NSNull null] ) {
            [_commandEncoder setFragmentTexture:_textureCache[i]
                                        atIndex:i];
        }
    }

    // set uniform buffer (force to bind to index 1 for now)
    if ( _shaderUniformBufferCache != nil ) {
        [_commandEncoder setVertexBuffer:_shaderUniformBufferCache
                                  offset:0
                                 atIndex:1];
        [_commandEncoder setFragmentBuffer:_shaderUniformBufferCache
                                  offset:0
                                 atIndex:1];
    }
}

- (id<MTLRenderPipelineState>)getRenderPipelineStateFromContext_:(GlobalContext*)context {
    assert(self.rpsCacheKey);
    id<MTLRenderPipelineState> state = self.renderPipelineStateCache[self.rpsCacheKey];

    if ( state == nil ) {
        state = [self newRenderPipelineStateFromContext_:context];
        self.renderPipelineStateCache[self.rpsCacheKey] = state;
    }

    return state;
}

- (id<MTLRenderPipelineState>)newRenderPipelineStateFromContext_:(GlobalContext*)context {
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
    vd.attributes[3].format = MTLVertexFormatFloat;
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
