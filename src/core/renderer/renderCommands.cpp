#include "core/renderer/renderCommands.h"
#include "backend/OpenGL/GLrenderAPI.h"

namespace Engine7414
{
    Scoped<RenderAPI> RenderCommands::__backend__;

    void RenderCommands::init(RendererBackend backend) {
        switch (backend) {
            case RendererBackend::OpenGL:
            {
                __backend__.reset( new GLRenderAPI );
                CORE_INFO( "\tBackend:  OpenGL" );
                break;
            }
            default: CORE_ASSERT( false, "Unsupported Backend" );
        }
        __backend__->init();
    }

    RendererBackend RenderCommands::getBackend() {
        return __backend__->backend();
    }

    void RenderCommands::setViewPort(const uint32_t& x, const uint32_t& y, const uint32_t& width, const uint32_t& height) {
        __backend__->setViewPort(x, y, width, height);
    }

    void RenderCommands::clear() {
        __backend__->clear();
    }

    void RenderCommands::clear(const glm::vec4& color) {
        __backend__->setClearColor( color );
        __backend__->clear();
    }

    void RenderCommands::drawElement(const Ref<VertexArray>& vertexArray, const uint32_t& indexCount) {
        __backend__->drawElement( vertexArray, indexCount );
    }
}
