#include "core/renderer/frameBuffer.h"
#include "core/renderer/renderer.h"
#include "backend/OpenGL/GLframeBuffer.h"

namespace Engine7414
{
    // default clear values for depth and stencil buffer are 1.0 and 0.0
    const FrameBufferTextureClearData FrameBufferTextureClearData::DEFAULT_CLEAR_DEPTH(1.0f, 0);
    
    // default clear color is opaque black
    const FrameBufferTextureClearData FrameBufferTextureClearData::DEFAULT_CLEAR_COLOR(0.0f, 0.0f, 0.0f, 1.0f);

    Ref<FrameBuffer> FrameBuffer::create(const FrameBufferSpec& spec) {
        switch (Renderer::backend()) {
            case RendererBackend::OpenGL: return CreateRef<GLFrameBuffer>(spec);
            default: CORE_ASSERT(false, "Unsupported Backend");
        }
        return NULL;
    }

    bool FrameBuffer::isDepthFormat(const FrameBufferTextureFormat& format) {
        switch (format) {
            case FrameBufferTextureFormat::DEPTH24STENCIL8: return true;
        }
        return false;
    }

    FrameBuffer::FrameBuffer(const FrameBufferSpec& spec) {
        for (const auto& textureDesc : spec.attachments.attachments) {
            if (FrameBuffer::isDepthFormat(textureDesc.format)) {
                _depthAttachmentDesc = textureDesc;
            }
            else {
                _colorAttachmentDescs.push_back(textureDesc);
            }
        }
        _spec = spec;
    }

}
