#include "core/renderer/vertexArray.h"
#include "core/renderer/renderer.h"
#include "backend/OpenGL/GLvertexArray.h"

namespace Engine7414
{
    Ref<VertexArray> VertexArray::create() {
        switch (Renderer::backend()) {
            case RendererBackend::OpenGL: return CreateRef<GLVertexArray>();
            default: CORE_ASSERT( false, "Unsupported Backend" );
        }
        return NULL;
    }
}
