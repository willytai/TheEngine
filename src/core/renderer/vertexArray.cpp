#include "core/renderer/vertexArray.h"
#include "core/renderer/renderer.h"
#include "backend/OpenGL/GLvertexArray.h"
#include "backend/MTL/MTLvertexArray.h"

namespace Engine7414
{
    Ref<VertexArray> VertexArray::create() {
        switch (Renderer::backend()) {
            case RendererBackend::OpenGL: return CreateRef<GLVertexArray>();
            case RendererBackend::Metal: return CreateRef<MTLVertexArray>();
            default: CORE_ASSERT( false, "Unsupported Backend" );
        }
        return NULL;
    }
}
