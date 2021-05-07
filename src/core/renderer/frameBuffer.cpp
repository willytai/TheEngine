#include "core/renderer/frameBuffer.h"
#include "core/renderer/renderer.h"
#include "backend/OpenGL/GLframeBuffer.h"

#import "backend/MTL/MTLframeBuffer.h"

namespace Engine7414
{
    Ref<FrameBuffer> FrameBuffer::create(const FrameBufferSpec& spec) {
        switch (Renderer::backend()) {
            case RendererBackend::OpenGL: return CreateRef<GLFrameBuffer>(spec);
            case RendererBackend::Metal: return CreateRef<MTLFrameBuffer>(spec);
            default: CORE_ASSERT(false, "Unsupported Backend");
        }
        return NULL;
    }
}
