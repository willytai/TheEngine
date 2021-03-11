#include "core/renderer/renderCommands.h"
#include "backend/OpenGL/GLrenderAPI.h"

namespace Engine7414
{
    RenderAPI* RenderCommands::__backend__ = NULL;

    void RenderCommands::setBackend(RendererBackend backend) {
        if ( __backend__ ) delete __backend__;
        switch (backend) {
            case RendererBackend::OpenGL: __backend__ = new GLRenderAPI; break;
            default: CORE_ASSERT( false, "Unsupported Backend" );
        }
    }

    RendererBackend RenderCommands::getBackend() {
        return __backend__->backend();
    }

    void RenderCommands::clear() {
        __backend__->clear();
    }

    void RenderCommands::clear(const glm::vec4& color) {
        __backend__->setClearColor( color );
        __backend__->clear();
    }

    void RenderCommands::drawElement(const VertexArray* vertexArray) {
        __backend__->drawElement( vertexArray );
    }
}
