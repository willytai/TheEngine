#include "main/engine/layer2D.h"

Layer2D::Layer2D(const char* name) :
    Layer(name),
    _color({ 0.8f, 0.2f, 0.3f, 1.0f })
{

}

void Layer2D::onAttach() {
    _cameraController.createCamera2D(1280.0f / 960.0f);
    _texture = Engine7414::Texture2D::create("./resource/texture/instagram.png");
    _texture1 = Engine7414::Texture2D::create("./resource/texture/logo.png");
}

void Layer2D::onEvent(Engine7414::Event& event) {
    _cameraController.onEvent(event);
}

void Layer2D::onImGui() {
    auto stat = Engine7414::Renderer2D::stat();
    ImGui::Begin("Test");
    ImGui::Text( "drawCalls: %d", stat.drawCalls );
    ImGui::Text( "quadCount: %d", stat.quadCount );
    ImGui::ColorEdit4("color", &_color.r);
    ImGui::End();
}

void Layer2D::onUpdate(const Engine7414::TimeStep& deltaTime) {
    _cameraController.onUpdate(deltaTime);
    Engine7414::Renderer2D::beginScene(_cameraController.getCamera());
    Engine7414::Renderer2D::drawQuad({ 1.0f, 0.0f, 0.1f }, { 0.3f, 0.3f }, _texture);
    Engine7414::Renderer2D::drawQuad({ -1.0f, 0.0f }, { 1.0f, 1.0f }, _texture1);
    Engine7414::Renderer2D::drawQuad({ 1.0f, 0.0f }, { 0.5f, 1.0f }, _color);
    Engine7414::Renderer2D::endScene();
}
