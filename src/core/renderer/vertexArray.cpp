#include "core/renderer/vertexArray.h"
#include "core/renderer/renderer.h"

#ifdef __APPLE__
#import "backend/MTL/MTLvertexArray.h"
#else
#include "backend/OpenGL/GLvertexArray.h"
#endif

namespace Engine7414
{
    Ref<VertexArray> VertexArray::create() {
        switch (Renderer::backend()) {
            case RendererBackend::OpenGL:
            {
            #ifdef __APPLE__
                CORE_WARN( "OpenGL not supported on OS X, forcing Metal backend" );
                [[clang::fallthrough]];
            #else
                return CreateRef<GLVertexArray>();
            #endif
            }
            case RendererBackend::Metal: return CreateRef<MTLVertexArray>();
            default: CORE_ASSERT( false, "Unsupported Backend" );
        }
        return NULL;
    }
}
