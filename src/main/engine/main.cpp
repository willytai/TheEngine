#define ENGINE_INCLUDE_MAIN
#include "engine.h"

// for API testing
class simpleLayer : public Engine7414::Layer
{
public:
    simpleLayer(const char* name)
        : Layer(name)
    {
        _frameBuffer = Engine7414::FrameBuffer::create({1280, 960});
    }

    void onUpdate(const Engine7414::TimeStep& deltaTime) override {
        _frameBuffer->bind();
        Engine7414::Renderer2D::beginTest(_clearColor);
        Engine7414::Renderer2D::endTest();
        _frameBuffer->unbind();
    }

    void onImGui() override {
        ImGui::Begin( "Test" );
        ImGui::Text( "hellooooooooooooooooooooooo" );
        ImGui::ColorEdit4( "clear color", &_clearColor[0] );
        ImGui::Text( "frame rate: %.0f", ImGui::GetIO().Framerate);
        ImGui::End();

        ImGui::Begin( "framebuffer test" );
        ImGui::Image( _frameBuffer->colorAttachmentID(), ImVec2(128, 96) );
        ImGui::End();

        ImGui::ShowDemoWindow();
    }

    void onEvent(Engine7414::Event& event) override {
    }

private:
    glm::vec4                    _clearColor = {1.0f, 0.0f, 0.0f, 1.0f};
    Engine7414::Ref<Engine7414::FrameBuffer> _frameBuffer;
};


class sandbox : public Engine7414::App
{
public:
    sandbox(Engine7414::RendererBackend backend)
    : Engine7414::App(backend) {
        // this->pushLayer(new Layer2D("Layer2D test"));
        this->pushLayer( new simpleLayer("simple layer") );
    }
    ~sandbox() {}
};

#ifndef DEFAULT_CREATE_APP
Engine7414::App* Engine7414::appCreate(int argc, char** argv) {
    // a better font type/size
    Engine7414::FontLoader::loadFromFile({ "./misc/fontawesome/otfs/Brands-Regular-400.otf", 16.0f });
    return new sandbox(Engine7414::RendererBackend::Metal); }
#endif
