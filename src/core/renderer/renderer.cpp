#include "core/renderer/renderer.h"

namespace Engine7414
{
    Renderer::sceneData Renderer::__data__;

    void Renderer::init(RendererBackend backend) {
        CORE_INFO( "Renderer Info" );
        RenderCommands::init(backend);
    }

    void Renderer::onWindowResize(WindowResizeEvent& event) {
        RenderCommands::setViewPort(0, 0, event.width(), event.height());
    }

    void Renderer::beginScene(const Ref<CameraBase>& camera, const glm::vec4& color) {
        RenderCommands::clear( color );
        __data__.ProjViewMat = camera->projXview();
    }

    void Renderer::submit(const Ref<Shader>& shader, const Ref<VertexArray>& vertexArray) {
        shader->bind();
        shader->setMat4f( "u_ProjViewMat" , __data__.ProjViewMat );
        shader->setMat4f( "u_ModelMat", vertexArray->getModelMat() );
        vertexArray->bind();
        RenderCommands::drawElement( vertexArray );
    }

    void Renderer::endScene() {

    }
}
