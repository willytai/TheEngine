#include "core/renderer/renderer.h"
#include "core/renderer/renderer2D.h"
#include "core/renderer/renderCommands.h"
#include "core/renderer/rendererData.h"

namespace Engine7414
{
    static RendererData2D* __data; // allocating on the heap for life time control

    glm::mat4 Renderer2D::__ProjViewMatCache__;
    bool Renderer2D::__updateProjViewMat__ = true;

    void Renderer2D::setUpdateMatFlag() {
        __updateProjViewMat__ = true;
    }

    Ref<Texture2D> testTex;
    void Renderer2D::init() {
        testTex = Texture2D::create("./resource/texture/logo.png");
        CORE_ASSERT( testTex, "" );
        __data = new RendererData2D;

#ifdef _WIN64
        __data->textureShader = ShaderDict::get().load("C:\\Users\\Willy\\Desktop\\TheEngine\\TheEngine\\resource\\shader\\texture");
#else
        __data->textureShader = ShaderDict::get().load("./resource/shader/texture");
#endif
        int* samplers = new int[(uint32_t)__data->maxTextureSlots];
        for (int i = 0; i < __data->maxTextureSlots; ++i) {
            samplers[i] = i;
        }
        __data->textureShader->bind();
        __data->textureShader->setIntArray("u_Samplers", samplers, __data->maxTextureSlots );

        uint32_t white = 0xffffffff;
        __data->textureSlots[0] = Texture2D::create( 1, 1, &white );

        // assuming imidiate upload to GPU
        delete[] samplers;
    }

    void Renderer2D::shutdown() {
        delete __data;
    }

    // ----------------------------------- temporary -----------------------------------------
    void Renderer2D::beginTest(const glm::vec4& color) {
        RenderCommands::clear( color );
        RenderCommands::begin();
    }

    void Renderer2D::triangleTest() {
        Renderer2D::drawQuad( {0.25f, 0.25f}, {0.5f, 0.5f}, {0.0f, 0.0f, 1.0f, 1.0f} );
        Renderer2D::drawQuad( {-0.25f, -0.25f}, {0.5f, 0.5f}, testTex );
        Renderer2D::flush();
    }

    void Renderer2D::endTest() {
        RenderCommands::end();
    }
    // ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^ temporary ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

    void Renderer2D::beginScene(const TransformComponent& transformComponent, const CameraBase* camera, const glm::vec4& color) {
        RenderCommands::clear(color);
        RenderCommands::begin();

        if (__updateProjViewMat__) {
            __ProjViewMatCache__ = camera->projection() *
                                   glm::inverse(transformComponent.transform());
            __updateProjViewMat__ = false;
            CORE_INFO("projview recalculated");
        }

        __data->stats.reset();
        __data->textureShader->bind();
        __data->textureShader->setMat4f("u_ProjViewMat", __ProjViewMatCache__);
    }

    void Renderer2D::endScene() {
        if ( __data->curIndexCount ) Renderer2D::flush();
        RenderCommands::end();
    }

    void Renderer2D::flush() {
        // bind all texture
        for (int slot = 0; slot < __data->curTextureID; ++slot) {
            __data->textureSlots[slot]->bind( (uint32_t)slot );
        }
        // upload data
        __data->quadVertexBuffer->setData(__data->vertexData,
                                          (size_t)(__data->vertexDataPtr - __data->vertexData) * sizeof(Vertex2D));
        // draw
        __data->quadVertexArray->bind();
        RenderCommands::drawElement(__data->quadVertexArray, __data->curIndexCount);
        // reset __data
        __data->reset();
        // stats
        __data->stats.drawCalls++;
    }

    void Renderer2D::drawQuad(const glm::vec2& position, const glm::vec2& size, const glm::vec4& color) {
         Renderer2D::drawQuad({position.x, position.y, 0.0f}, size, color);
    }

    void Renderer2D::drawQuad(const glm::vec2& position, const glm::vec2& size, const Ref<Texture2D>& texture) {
         Renderer2D::drawQuad({ position.x, position.y, 0.0f }, size, texture);
    }

    void Renderer2D::drawQuad(const glm::vec3& position, const glm::vec2& size, const glm::vec4& color) {
         Renderer2D::drawQuad( position, size, color, __data->textureSlots[0] );
    }

    void Renderer2D::drawQuad(const glm::vec3& position, const glm::vec2& size, const Ref<Texture2D>& texture) {
         Renderer2D::drawQuad( position, size, glm::vec4(1.0f), texture );
    }

    void Renderer2D::drawQuad(const glm::vec3& position, const glm::vec2& size, const glm::vec4& color, const Ref<Texture2D>& texture) {
        auto transform = glm::translate( glm::mat4(1.0f), position ) *
                         glm::scale( glm::mat4(1.0f), glm::vec3(size.x, size.y, 1.0f) );
        Renderer2D::drawQuad( transform, color, texture );
    }

    void Renderer2D::drawQuad(const glm::mat4& transform, const glm::vec4& color) {
         Renderer2D::drawQuad( transform, color, __data->textureSlots[0] );
    }

    void Renderer2D::drawQuad(const glm::mat4& transform, const glm::vec4& color, const Ref<Texture2D>& texture) {
        int textureID = -1;
        for (int i = 0; i < __data->curTextureID; ++i) {
            if ( texture.get() == __data->textureSlots[i].get() ) {
                textureID = i;
                break;
            }
        }
        if ( textureID == -1 ) {
            textureID = (int)__data->curTextureID;
            __data->textureSlots[textureID] = texture;
            ++__data->curTextureID;
        }

        for (uint32_t i = 0; i < 4; ++i) {
            __data->vertexDataPtr->color     = color;
            __data->vertexDataPtr->texCoor   = __data->textureCoords[i];
            __data->vertexDataPtr->position  = transform * __data->unitQuadVertices[i];
            __data->vertexDataPtr->samplerID = (float)textureID;
            __data->vertexDataPtr++;
        }

        __data->curIndexCount += 6;
        __data->stats.quadCount++;

        if ( __data->shouldFlush() ) Renderer2D::flush();
    }

    Renderer2D::statistics Renderer2D::stat() {
        return __data->stats;
    }

    void Renderer2D::resetStat() {
        __data->stats.reset();
    }
}
