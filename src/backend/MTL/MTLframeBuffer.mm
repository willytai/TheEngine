#import "backend/MTL/MTLrenderAPI.h"
#import "backend/MTL/MTLframeBuffer.h"
#import "backend/MTL/MTLcontext.h"

// @implementation MTLFrameBufferKey
// - (instancetype)initWithHandle:(MTLFrameBufferHandle*)handle {
//     if ( (self = [super init]) ) {
//         _colorPixelFormat = handle.colorAttachment.pixelFormat;
//         _depthPixelFormat = handle.depthAttachment.pixelFormat;
//         _stencilPixelFormat = handle.depthAttachment.pixelFormat;
// 
//         // TODO sample count is something that is not yet used
//         _sampleCount = 1;
//     }
//     return self;
// }
// - (nonnull id)copyWithZone:(NSZone*)zone {
//     MTLFrameBufferKey* copy = [[MTLFrameBufferKey allocWithZone:zone] init];
//     copy.sampleCount = self.sampleCount;
//     copy.colorPixelFormat = self.colorPixelFormat;
//     copy.depthPixelFormat = self.depthPixelFormat;
//     copy.stencilPixelFormat = self.stencilPixelFormat;
//     return copy;
// }
// @end

@implementation MTLFrameBufferHandle
- (instancetype) initWithDimensionWidth:(uint32_t)width Height:(uint32_t)height {
    if ( (self = [super init]) ) {
        auto* device = Engine7414::MTLContext::getContext().nativeDevice;

        // -- color attachment format
        _colorAttachmentDiscriptor = [[MTLTextureDescriptor alloc] init];
        _colorAttachmentDiscriptor.textureType = MTLTextureType2D;
        _colorAttachmentDiscriptor.pixelFormat = MTLPixelFormatRGBA8Unorm;
        _colorAttachmentDiscriptor.width = width;
        _colorAttachmentDiscriptor.height = height;
        _colorAttachmentDiscriptor.depth = 1;
        _colorAttachmentDiscriptor.mipmapLevelCount = 1;
        _colorAttachmentDiscriptor.usage = MTLTextureUsageRenderTarget;
        // _colorAttachmentDiscriptor.storageMode = MTLStorageModePrivate; // not sure of this
        _colorAttachment = [device newTextureWithDescriptor:_colorAttachmentDiscriptor];

        // -- depth/stencil attachment format
        _depthAttachmentDiscriptor = [[MTLTextureDescriptor alloc] init];
        _depthAttachmentDiscriptor.textureType = MTLTextureType2D;
        _depthAttachmentDiscriptor.pixelFormat = MTLPixelFormatDepth32Float_Stencil8;
        _depthAttachmentDiscriptor.width = width;
        _depthAttachmentDiscriptor.height = height;
        _depthAttachmentDiscriptor.depth = 1;
        _depthAttachmentDiscriptor.mipmapLevelCount = 1;
        _depthAttachmentDiscriptor.usage = MTLTextureUsageRenderTarget;
        _depthAttachmentDiscriptor.storageMode = MTLStorageModePrivate;
        _depthAttachment = [device newTextureWithDescriptor:_depthAttachmentDiscriptor];

        // -- sampler
        MTLSamplerDescriptor* samplerDescriptor = [[MTLSamplerDescriptor alloc] init];
        samplerDescriptor.minFilter = MTLSamplerMinMagFilterLinear;
        samplerDescriptor.magFilter = MTLSamplerMinMagFilterLinear;
        _sampler = [device newSamplerStateWithDescriptor:samplerDescriptor];

        // -- create cache key
        // _cacheKey = [[MTLFrameBufferKey alloc] initWithHandle:self];
    }
    return self;
}
- (void) reGenWithDimensionWidth:(uint32_t)width Height:(uint32_t)height {
    auto* device = Engine7414::MTLContext::getContext().nativeDevice;
    _colorAttachmentDiscriptor.width = width;
    _colorAttachmentDiscriptor.height = height;
    _colorAttachment = [device newTextureWithDescriptor:_colorAttachmentDiscriptor];
    _depthAttachmentDiscriptor.width = width;
    _depthAttachmentDiscriptor.height = height;
    _depthAttachment = [device newTextureWithDescriptor:_depthAttachmentDiscriptor];
    // _cacheKey = [[MTLFrameBufferKey alloc] initWithHandle:self];
}
@end

namespace Engine7414
{
    MTLFrameBuffer::MTLFrameBuffer(const FrameBufferSpec& spec) :
        _handle(nil),
        _spec(spec)
    {
        _handle = [[MTLFrameBufferHandle alloc] initWithDimensionWidth:_spec.width Height:_spec.height];
    }

    MTLFrameBuffer::~MTLFrameBuffer() {
    }

    void MTLFrameBuffer::regenerate() {
        [_handle reGenWithDimensionWidth:_spec.width Height:_spec.height];
    }

    void MTLFrameBuffer::bind() const {
        // set the attachment to the discriptor of the renderer
        auto* renderHandle = MTLRenderAPI::getRenderHandle();
        renderHandle.renderPassDescriptor.colorAttachments[0].texture = _handle.colorAttachment;
        renderHandle.renderPassDescriptor.depthAttachment.texture = _handle.depthAttachment;
        renderHandle.renderPassDescriptor.stencilAttachment.texture = _handle.depthAttachment;
        renderHandle.rpsCacheKey.colorPixelFormat = _handle.colorAttachment.pixelFormat;
        renderHandle.rpsCacheKey.depthPixelFormat = _handle.depthAttachment.pixelFormat;
        renderHandle.rpsCacheKey.stencilPixelFormat = _handle.depthAttachment.pixelFormat;

        // TODO sample count is something that is not yet used
        renderHandle.rpsCacheKey.sampleCount = 1;
    }

    void MTLFrameBuffer::unbind() const {
    }

    void MTLFrameBuffer::resize(const uint32_t& width, const uint32_t& height) {
        _spec.width = width;
        _spec.height = height;
        this->regenerate();
    }

    void* MTLFrameBuffer::colorAttachmentID() const {
        return (__bridge void*)_handle.colorAttachment;
    }
}
