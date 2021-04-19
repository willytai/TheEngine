#include "core/renderer/renderer.h"
#include "core/renderer/rendererData.h"

namespace Engine7414
{
    Renderer::sceneData Renderer::__data__;
    bool Renderer::__updateProjViewMat__ = true;

    void Renderer::setUpdateMatFlag() {
        __updateProjViewMat__ = true;
    }

    void Renderer::setMaxTextSlot(const int& maxSlot) {
        RendererData2D::setMaxTextSlot( maxSlot );
    }

    void Renderer::init(RendererBackend backend) {
        CORE_INFO( "Renderer Info" );
        RenderCommands::init(backend);
        Renderer2D::init();
    }

    void Renderer::shutdown() {
        Renderer2D::shutdown();
    }

    void Renderer::onWindowResize(WindowResizeEvent& event) {
        RenderCommands::setViewPort(0, 0, event.width(), event.height());
    }

    void Renderer::beginScene(const Ref<CameraBase>& camera, const glm::vec4& color) {
        RenderCommands::clear( color );
        CORE_ASSERT(false, "{} Not Implemented!", __PRETTY_FUNCTION__);
    }

    void Renderer::submit(const Ref<Shader>& shader, const Ref<VertexArray>& vertexArray) {
        shader->bind();
        shader->setMat4f( "u_ProjViewMat" , __data__.ProjViewMat ); // TODO change this (very inefficient!)
        shader->setMat4f( "u_ModelMat", vertexArray->getModelMat() );
        vertexArray->bind();
        RenderCommands::drawElement( vertexArray );
    }

    void Renderer::endScene() {

    }
}
