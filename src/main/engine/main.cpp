#define ENGINE_INCLUDE_MAIN
#include "engine.h"
#include "main/engine/layer2D.h"

// for API testing
class simpleLayer : public Engine7414::Layer
{
public:
    simpleLayer(const char* name)
        : Layer(name)
    {
        _cameraController.createCamera2D(1280.0f / 960.0f);
    }

    void onUpdate(const Engine7414::TimeStep& deltaTime) override {
        Engine7414::Renderer::beginScene( _cameraController.getCamera(), _clearColor );
        Engine7414::Renderer::endScene();
    }

    void onImGui() override {
        ImGui::Begin( "Test" );
        ImGui::Text( "hellooooooooooooooooooooooo" );
        ImGui::ColorEdit4( "clear color", &_clearColor[0] );
        ImGui::Text( "frame rate: %.0f", ImGui::GetIO().Framerate);
        ImGui::End();
    }

    void onEvent(Engine7414::Event& event) override {
    }

private:
    Engine7414::CameraController _cameraController;
    glm::vec4                    _clearColor = {1.0f, 0.0f, 0.0f, 1.0f};
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
    Engine7414::FontLoader::loadFromeFile({ "./misc/fontawesome/otfs/Brands-Regular-400.otf", 16.0f });
    return new sandbox(Engine7414::RendererBackend::Metal); }
#endif
