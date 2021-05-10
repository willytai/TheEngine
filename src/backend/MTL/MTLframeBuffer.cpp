#include "backend/MTL/MTLrenderAPI.h"
#include "backend/MTL/MTLframeBuffer.h"
#include "backend/MTL/MTLcontext.h"

namespace Engine7414
{
    MTLFrameBuffer::MTLFrameBuffer(const FrameBufferSpec& spec) :
        _handle(nil),
        _spec(spec)
    {
        _handle = [[MTLFrameBufferHandle alloc] initWithDimensionWidth:_spec.width
                                                                Height:_spec.height
                                                                Device:MTLContext::getContext().nativeDevice];
    }

    MTLFrameBuffer::~MTLFrameBuffer() {
    }

    void MTLFrameBuffer::regenerate() {
        [_handle reGenWithDimensionWidth:_spec.width
                                  Height:_spec.height
                                  Device:MTLContext::getContext().nativeDevice];
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
