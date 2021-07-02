#include "core/renderer/renderer.h"
#include "core/renderer/renderer2D.h"
#include "core/renderer/renderCommands.h"
#include "core/renderer/rendererData2D.h"

#include <glm/gtc/type_ptr.hpp>

namespace Engine7414
{
    static RendererData2D* __data; // allocating on the heap for life time control

    std::vector<UniformHandle> Renderer2D::_globalUniformHandle;

    glm::mat4 Renderer2D::__ProjViewMatCache__;
    bool Renderer2D::__updateProjViewMat__ = true;

    void Renderer2D::setUpdateMatFlag() {
        __updateProjViewMat__ = true;
    }

    void Renderer2D::init() {
        __data = new RendererData2D;

        // vertex buffer
        __data->quadVertexBuffer = VertexBuffer::create(__data->maxVertexCount*sizeof(Vertex2D));
        __data->quadVertexBuffer->setLayout(
            {
                {BufferDataType::Float, 3}, // position
                {BufferDataType::Float, 4}, // color
                {BufferDataType::Float, 2}, // texture coordinates
                {BufferDataType::Int,   1}, // texture samplerID
                {BufferDataType::Int,   1}  // entity ID
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
        __data->textureShader = ShaderLibrary::get().load("C:\\Users\\Willy\\Desktop\\TheEngine\\TheEngine\\resource\\shader\\texture");
#else
        __data->textureShader = ShaderLibrary::get().load("./resource/shader/texture");
#endif
        // int* samplers = new int[(uint32_t)__data->maxTextureSlots];
        // for (int i = 0; i < __data->maxTextureSlots; ++i) {
        //     samplers[i] = i;
        // }
        // __data->textureShader->bind();
        //__data->textureShader->setIntArray("u_Samplers", samplers, __data->maxTextureSlots );

        uint32_t white = 0xffffffff;
        __data->textureSlots[0] = Texture2D::create( 1, 1, &white );

        // assuming imidiate upload to GPU
        delete[] indices32UI;
        // delete[] samplers;

        Renderer2D::registerGlobalUniform();
    }

    void Renderer2D::registerGlobalUniform() {
        // the view projection matrix, binding point: 0, uniform block: Camera
        if (_globalUniformHandle.size() < G_UNIFORM_PROJ_VIEW_MAT + 1) {
            _globalUniformHandle.resize(G_UNIFORM_PROJ_VIEW_MAT + 1);
            auto& handle = _globalUniformHandle[G_UNIFORM_PROJ_VIEW_MAT];
            handle.name = "Camera::ProjViewMat";
            handle.bindingIndex = 0;
            handle.offset = 0;
            handle.size = sizeof(glm::mat4);
        }

        // register and submit
        for (auto& handle : _globalUniformHandle)
            ShaderLibrary::registerGlobalUniform(handle);
        ShaderLibrary::submitGlobalUniforms();
    }

    void Renderer2D::shutdown() {
        delete __data;
    }

    void Renderer2D::beginScene(const TransformComponent& transformComponent, const CameraBase* camera, const glm::vec4& color) {
        RenderCommands::clear(color);

        // set global uniform: view projection matrix
        auto& cameraProjection = camera->projection();
        if (__updateProjViewMat__) {
            __ProjViewMatCache__ = cameraProjection *
                                   glm::inverse(transformComponent.transform());
            __updateProjViewMat__ = false;

            CORE_INFO("projview recalculated");
            // link the data
            _globalUniformHandle[G_UNIFORM_PROJ_VIEW_MAT].data = &__ProjViewMatCache__[0];
        }

        ShaderLibrary::uploadGlobalUniforms(_globalUniformHandle);
        
        __data->stats.reset();
        // __data->textureShader->bind();
        // __data->textureShader->setMat4f("u_ProjViewMat", __ProjViewMatCache__);
    }

    void Renderer2D::beginScene(Ref<EditorCamera>& camera, const Ref<FrameBuffer>& currentFrameBuffer, const glm::vec4& defaultFrameBufferClearColor) {
        RenderCommands::clear(defaultFrameBufferClearColor);
        currentFrameBuffer->clear();
        __data->stats.reset();

        // link the data
        // NOTE: the data has to stay fixed, otherwise this breaks
        _globalUniformHandle[G_UNIFORM_PROJ_VIEW_MAT].data = glm::value_ptr(camera->getViewProjection());

        // upload to GPU
        ShaderLibrary::uploadGlobalUniforms(_globalUniformHandle);

        // __data->textureShader->bind();
        // __data->textureShader->setMat4f("u_ProjViewMat", camera->getViewProjection());
    }


    void Renderer2D::endScene() {
        if ( __data->curIndexCount ) Renderer2D::flush();
    }

    void Renderer2D::flush() {
        // bind all texture
        for (int slot = 0; slot < __data->curTextureID; ++slot) {
            __data->textureSlots[slot]->bind( (uint32_t)slot );
        }
        // bind shader
        __data->textureShader->bind();
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
        Renderer2D::drawQuad( transform, color, texture, 0 );
    }

    void Renderer2D::drawQuad(const glm::mat4& transform, const glm::vec4& color) {
         Renderer2D::drawQuad( transform, color, __data->textureSlots[0], 0 );
    }

    void Renderer2D::drawQuad(const glm::mat4& transform, const glm::vec4& color, int enttID) {
        Renderer2D::drawQuad(transform, color, __data->textureSlots[0], enttID);
    }

    void Renderer2D::drawQuad(const glm::mat4& transform, const glm::vec4& color, const Ref<Texture2D>& texture, const int& enttID) {
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
            __data->vertexDataPtr->samplerID = textureID;
            __data->vertexDataPtr->entityID  = enttID;
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
