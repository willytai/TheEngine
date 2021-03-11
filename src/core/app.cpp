#include "core/app.h"

#include "core/renderer/buffer.h"
#include "core/renderer/shader.h"
#include "core/renderer/vertexArray.h"
#include "core/renderer/renderer.h"
#include "backend/OpenGL/GLmacro.h"
#include "glad/glad.h"

#ifdef DEFAULT_CREATE_APP
Engine7414::App* Engine7414::appCreate(int argc, char** argv) {
    // TODO parser stuff, control verbosity here
    return new Engine7414::App;
}
#endif

namespace Engine7414
{
    // to make sure that only one application exists
    App* App::appInstancePtr = NULL;

    App::App(RendererBackend backend, int verbosity) :
        _shouldRun(true),
        _minimized(false)
    {
        if ( appInstancePtr ) {
            CORE_ASSERT( false, "Application already exists! You cannot create another one!" );
        }
        else appInstancePtr = this;

        // initialize logger
        util::Log::init( verbosity );
        CORE_INFO( "engine initializing" );

        // initialize renderer
        Renderer::init( backend );

        // default window
        _window = std::unique_ptr<Window>(Window::create( "Engine7414", 1280, 960, backend, true ));
        _window->setEventCallback( CORE_BIND_EVENT_FN(App::onEvent) );

        // ImGui layer
        this->pushOverlay( _imguiLayer = new ImGuiLayer );
    }

    App::~App() {}

    void App::run() {
        float vertices[] = {
            -0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f,
             0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f,
             0.0f,  0.5f, 0.0f, 0.0f, 0.0f, 1.0f
        };
        uint8_t indices[] = { 0, 1, 2 };
        auto vb = VertexBuffer::create( vertices, 18*sizeof(float) );
        vb->setLayout({
            { BufferDataType::Float, 3 },
            { BufferDataType::Float, 3 }
        });
        auto va = VertexArray::create();
        va->addVertexBuffer( vb );
        auto ib = IndexBufferUI8::create( indices, 3 );
        auto shader = Shader::create( "./resource/shader/basic/vertex.glsl",
                                      "./resource/shader/basic/fragment.glsl" );
        va->setIndexBuffer( ib );
        shader->bind();

        CORE_INFO( "engine started" );
        while ( _shouldRun ) {
            if ( !_minimized ) {
                for (auto* layer : _layerStack) {
                    layer->onUpdate();
                }
                _imguiLayer->begin();
                for (auto* layer : _layerStack) {
                    layer->onImGui();
                }
                _imguiLayer->end();
            }
            Renderer::beginScene();
            Renderer::submit(va);
            Renderer::endScene();
            _window->onUpdate();
        }
        this->shutdown();
    }

    void App::onEvent(Event& event) {
        EventDispatcher dispatcher( event );

        dispatcher.dispatch<WindowCloseEvent>( CORE_BIND_EVENT_FN(App::onWindowClose) );
        dispatcher.dispatch<WindowResizeEvent>( CORE_BIND_EVENT_FN(App::onWindowResize) );

        for (auto it = _layerStack.rbegin(); it != _layerStack.rend(); ++it) {
            if ( event.handled() ) break;
            (*it)->onEvent( event );
        }
    }

    void App::pushLayer(Layer* layer) {
        _layerStack.pushLayer( layer );
    }

    void App::pushOverlay(Layer* layer) {
        _layerStack.pushOverlay( layer );
    }

    bool App::onWindowClose(WindowCloseEvent& e) {
        _shouldRun = false;
        return true;
    }

    bool App::onWindowResize(WindowResizeEvent& e) {
        _minimized = false;
        return false;
    }

    bool App::onWindowIconify(WindowIconifyEvent& e) {
        _minimized = true;
        return false;
    }

    void App::shutdown() {
        glfwTerminate();
    }
}
