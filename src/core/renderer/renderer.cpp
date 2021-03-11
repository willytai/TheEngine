#include "core/renderer/renderer.h"

namespace Engine7414
{
    void Renderer::init(RendererBackend backend) {
        RenderCommands::setBackend(backend);
        CORE_INFO( "Renderer Backend: {}", STRINGIFY(OpenGL) );
    }

    void Renderer::beginScene(bool clear) {
        if ( clear ) RenderCommands::clear();
    }

    void Renderer::beginScene(const glm::vec4& color) {
        RenderCommands::clear( color );
    }

    void Renderer::submit(const VertexArray* vertexArray) {
        vertexArray->bind();
        RenderCommands::drawElement( vertexArray );
    }

    void Renderer::endScene() {

    }
}
