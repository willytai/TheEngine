#include "core/renderer/renderer2D.h"
#include "core/renderer/renderCommands.h"
#include "core/renderer/rendererData.h"

namespace Engine7414
{
    static RendererData2D* __data; // allocating on the heap for life time control

    void Renderer2D::init() {
        __data = new RendererData2D;

        // vertex buffer
        __data->quadVertexBuffer = VertexBuffer::create(__data->maxVertexCount*sizeof(Vertex2D));
        __data->quadVertexBuffer->setLayout(
            {
                {BufferDataType::Float, 3}, // position
                {BufferDataType::Float, 4}, // color
                {BufferDataType::Float, 2}, // texture coordinates
                {BufferDataType::Float, 1}  // texture samplerID
            }
        );

        // index buffer (counter-clockwise indexing)
        // might be large, doing heap allocation in case of stack overflow
        // TODO using Ref<> is probably better!
        uint32_t* indices32UI = new uint32_t[__data->maxIndexCount];
        for (uint32_t i = 0, offset = 0; i < __data->maxIndexCount; i += 6, offset += 4) {
            indices32UI[i + 0] = offset + 0;
            indices32UI[i + 1] = offset + 1;
            indices32UI[i + 2] = offset + 2;

            indices32UI[i + 3] = offset + 0;
            indices32UI[i + 4] = offset + 2;
            indices32UI[i + 5] = offset + 3;
        }

        // vertex array
        __data->quadVertexArray = VertexArray::create();
        __data->quadVertexArray->addVertexBuffer(__data->quadVertexBuffer);
        __data->quadVertexArray->setIndexBuffer(IndexBufferUI32::create(indices32UI, __data->maxIndexCount));

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
        delete[] indices32UI;
        delete[] samplers;
    }

    void Renderer2D::shutdown() {
        delete __data;
    }

    void Renderer2D::beginScene(const Ref<CameraBase>& camera, const glm::vec4& color) {
        RenderCommands::clear(color);

        __data->textureShader->bind();
        __data->textureShader->setMat4f("u_ProjViewMat", camera->projXview());
    }

    void Renderer2D::endScene() {
        Renderer2D::flush();
        __data->reset();
    }

    void Renderer2D::flush() {
        // bind all texture
        for (int slot = 0; slot < __data->curTextureID; ++slot) {
            __data->textureSlots[slot]->bind( (uint32_t)slot );
        }
        // upload data
        __data->quadVertexBuffer->setData(__data->vertexData,
                                          (size_t)(__data->vertexDataPtr - __data->vertexData) * sizeof(Vertex2D));
        __data->quadVertexArray->bind();
        RenderCommands::drawElement(__data->quadVertexArray, __data->curIndexCount);
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

        __data->vertexDataPtr->color = color;
        __data->vertexDataPtr->position = { position.x - size.x / 2.0f, position.y - size.y / 2.0f, position.z };
        __data->vertexDataPtr->texCoor = { 0.0f, 0.0f };
        __data->vertexDataPtr->samplerID = (float)textureID;
        __data->vertexDataPtr++;

        __data->vertexDataPtr->color = color;
        __data->vertexDataPtr->position = { position.x + size.x / 2.0f, position.y - size.y / 2.0f, position.z };
        __data->vertexDataPtr->texCoor = { 1.0f, 0.0f };
        __data->vertexDataPtr->samplerID = (float)textureID;
        __data->vertexDataPtr++;

        __data->vertexDataPtr->color = color;
        __data->vertexDataPtr->position = { position.x + size.x / 2.0f, position.y + size.y / 2.0f, position.z };
        __data->vertexDataPtr->texCoor = { 1.0f, 1.0f };
        __data->vertexDataPtr->samplerID = (float)textureID;
        __data->vertexDataPtr++;

        __data->vertexDataPtr->color = color;
        __data->vertexDataPtr->position = { position.x - size.x / 2.0f, position.y + size.y / 2.0f, position.z };
        __data->vertexDataPtr->texCoor = { 0.0f, 1.0f };
        __data->vertexDataPtr->samplerID = (float)textureID;
        __data->vertexDataPtr++;

        __data->curIndexCount += 6;

        if ( __data->shouldFlush() ) Renderer2D::flush();
    }
}
