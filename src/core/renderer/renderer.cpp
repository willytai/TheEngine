#include "core/renderer/renderer.h"

namespace Engine7414
{
    Renderer::sceneData Renderer::__data__;

    void Renderer::init(RendererBackend backend) {
        RenderCommands::setBackend(backend);
        CORE_INFO( "Renderer Backend: {}", STRINGIFY(OpenGL) );
    }

    void Renderer::beginScene(const Camera& camera, const glm::vec4& color) {
        RenderCommands::clear( color );
        __data__.ProjViewMat = camera.projXview();
    }

    void Renderer::submit(Shader* shader, const VertexArray* vertexArray) {
        shader->bind();
        shader->setMat4f( "u_ProjViewMat" , __data__.ProjViewMat );
        shader->setMat4f( "u_ModelMat", vertexArray->getModelMat() );
        vertexArray->bind();
        RenderCommands::drawElement( vertexArray );
    }

    void Renderer::endScene() {

    }
}
