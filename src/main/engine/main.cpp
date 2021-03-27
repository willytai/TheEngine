#include "engine.h"

class testLayer : public Engine7414::Layer
{
public:
    testLayer(const char* name)
        : Layer(name), _camera( 45, 1280.0f/960.0f )
    {
        float vertices[] = {
             // face of the cube         // color                   // texture coordinates
             -1.0f, -1.0f,  1.0f, 1.0f,  0.583f,  0.771f,  0.014f,  0.0f, 0.0f,
              1.0f, -1.0f,  1.0f, 1.0f,  0.822f,  0.569f,  0.201f,  1.0f, 0.0f,
              1.0f,  1.0f,  1.0f, 1.0f,  0.559f,  0.436f,  0.730f,  1.0f, 1.0f,
             -1.0f,  1.0f,  1.0f, 1.0f,  0.195f,  0.548f,  0.859f,  0.0f, 1.0f,
             // tail of the cube
             -1.0f, -1.0f, -1.0f, 1.0f,  0.140f,  0.616f,  0.489f,  0.0f, 0.0f,
              1.0f, -1.0f, -1.0f, 1.0f,  0.543f,  0.021f,  0.978f,  1.0f, 0.0f,
              1.0f,  1.0f, -1.0f, 1.0f,  0.055f,  0.953f,  0.042f,  1.0f, 1.0f,
             -1.0f,  1.0f, -1.0f, 1.0f,  0.225f,  0.587f,  0.040f,  0.0f, 1.0f
        };
        uint8_t indices[] = {
            0, 1, 2,
            0, 2, 3,
            4, 5, 6,
            4, 6, 7,
            3, 2, 6,
            3, 6, 7,
            0, 1, 5,
            0, 5, 4,
            0, 4, 7,
            0, 7, 3,
            1, 5, 6,
            1, 6, 2
        };

        _vertexBuffer = Engine7414::VertexBuffer::create( vertices, (4+3+2)*8*sizeof(float) );
        _vertexBuffer->setLayout({
            { Engine7414::BufferDataType::Float, 4 },
            { Engine7414::BufferDataType::Float, 3 },
            { Engine7414::BufferDataType::Float, 2 }
        });
        _vertexArray = Engine7414::VertexArray::create();
        _vertexArray->addVertexBuffer( _vertexBuffer );
        _indexBuffer = Engine7414::IndexBufferUI8::create( indices, 36 );
        _vertexArray->setIndexBuffer( _indexBuffer );
        _vertexArray->setModelMat( glm::translate( glm::mat4(1.0f), glm::vec3(0.0f, 2.0f, -10.0f) ) );
        _texture = Engine7414::Texture2D::create( "./resource/texture/logo.png" );
        _texture->bind();

        auto shader = Engine7414::Renderer::getShaderDict().load( "./resource/shader/texture" );
        shader->bind();
        shader->setInt1( "u_textureID", 0 );
    }

    void onUpdate(const Engine7414::TimeStep& deltaTime) override {
        if ( Engine7414::Input::keyPressed(Engine7414::Key::UP) ) {
            _camera.moveZ( -1.0f * deltaTime );
        }
        else if ( Engine7414::Input::keyPressed(Engine7414::Key::DOWN) ) {
            _camera.moveZ(  1.0f * deltaTime );
        }
        if ( Engine7414::Input::keyPressed(Engine7414::Key::RIGHT) ) {
            _camera.moveX( -1.0f * deltaTime );
        }
        else if ( Engine7414::Input::keyPressed(Engine7414::Key::LEFT) ) {
            _camera.moveX(  1.0f * deltaTime );
        }
        if ( Engine7414::Input::keyPressed(Engine7414::Key::A) ) {
            _camera.rotateX( -10.0f * deltaTime );
        }
        else if ( Engine7414::Input::keyPressed(Engine7414::Key::S) ) {
            _camera.rotateX(  10.0f * deltaTime );
        }
        if ( Engine7414::Input::keyPressed(Engine7414::Key::Q) ) {
            _camera.rotateY( -10.0f * deltaTime );
        }
        else if ( Engine7414::Input::keyPressed(Engine7414::Key::W) ) {
            _camera.rotateY(  10.0f * deltaTime );
        }

        Engine7414::Renderer::beginScene( _camera );
        Engine7414::Renderer::submit( Engine7414::Renderer::getShaderDict().get("texture"), _vertexArray );
        Engine7414::Renderer::endScene();
    }

    void onImGui() override {
        ImGui::Begin( "Test" );
        ImGui::Text( "hellooooooooooooooooooooooo" );
        ImGui::End();
    }

    void onEvent(Engine7414::Event& event) override {
        Engine7414::EventDispatcher dispatcher( event );
        dispatcher.dispatch<Engine7414::WindowResizeEvent>( CORE_BIND_EVENT_FN(testLayer::onWindowResize) );
    }

private:
    bool onWindowResize(Engine7414::WindowResizeEvent& event) {
        _camera.setAspect( (float)event.width(), (float)event.height() );
        return false;
    }

private:
    Engine7414::Ref<Engine7414::IndexBuffer> _indexBuffer;
    Engine7414::Ref<Engine7414::VertexArray>  _vertexArray;
    Engine7414::Ref<Engine7414::VertexBuffer> _vertexBuffer;
    Engine7414::Ref<Engine7414::Shader>       _shader;
    Engine7414::Ref<Engine7414::Texture2D>    _texture;
    Engine7414::Camera        _camera;
};


class sandbox : public Engine7414::App
{
public:
    sandbox(Engine7414::RendererBackend backend)
    : Engine7414::App(backend) {
        this->pushLayer( new testLayer( "background" ) );
    }
    ~sandbox() {}
};

#ifndef DEFAULT_CREATE_APP
Engine7414::App* Engine7414::appCreate(int argc, char** argv) {
    // a better font type/size
    Engine7414::FontLoader::loadFromeFile({ "./misc/fontawesome/otfs/Brands-Regular-400.otf", 16.0f });
    return new sandbox(Engine7414::RendererBackend::OpenGL); }
#endif
