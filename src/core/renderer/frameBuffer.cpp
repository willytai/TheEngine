#include "core/renderer/frameBuffer.h"
#include "core/renderer/renderer.h"

#ifdef __APPLE__
#import "backend/MTL/MTLframeBuffer.h"
#else
#include "backend/OpenGL/GLframeBuffer.h"
#endif

namespace Engine7414
{
    Ref<FrameBuffer> FrameBuffer::create(const FrameBufferSpec& spec) {
        switch (Renderer::backend()) {
            case RendererBackend::OpenGL:
            {
            #ifdef __APPLE__
                CORE_WARN( "OpenGL not supported on OS X, forcing Metal backend" );
                [[clang::fallthrough]];
            #else
                return CreateRef<GLFrameBuffer>(spec);
            #endif
            }
            case RendererBackend::Metal: return CreateRef<MTLFrameBuffer>(spec);
            default: CORE_ASSERT(false, "Unsupported Backend");
        }
        return NULL;
    }
}
