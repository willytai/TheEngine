#include "core/renderer/rendererData.h"

namespace Engine7414
{
    // counter-clockwise from bottom left
    glm::vec4 RendererData2D::unitQuadVertices[4] = {
        { -0.5f, -0.5f, 0.0f, 1.0f },
        {  0.5f, -0.5f, 0.0f, 1.0f },
        {  0.5f,  0.5f, 0.0f, 1.0f },
        { -0.5f,  0.5f, 0.0f, 1.0f }
    };

    glm::vec2 RendererData2D::textureCoords[4] = {
        { 0.0f, 0.0f },
        { 1.0f, 0.0f },
        { 1.0f, 1.0f },
        { 0.0f, 1.0f }
    };

    int RendererData2D::maxTextureSlots = 0;

    RendererData2D::RendererData2D() {
        CORE_ASSERT( maxTextureSlots > 0, "maximum texture slots not set before renderer initialization!" );

        // vertex buffer
        quadVertexBuffer = VertexBuffer::create(maxVertexCount*sizeof(Vertex2D));
        quadVertexBuffer->setLayout(
            {
                {BufferDataType::Float, 3}, // position
                {BufferDataType::Float, 4}, // color
                {BufferDataType::Float, 2}, // texture coordinates
                {BufferDataType::Float, 1}  // texture samplerID
            }
        );
        // the system storage, point to it if API already handles this, otherwise, allocate explicitly
        vertexData = quadVertexBuffer->getCPUStorage() ? static_cast<Vertex2D*>(quadVertexBuffer->getCPUStorage()) : new Vertex2D[maxVertexCount];

        // index buffer (counter-clockwise indexing)
        // might be large, doing heap allocation in case of stack overflow
        // TODO using Ref<> is probably better!
        uint32_t* indices32UI = new uint32_t[maxIndexCount];
        for (uint32_t i = 0, offset = 0; i < maxIndexCount; i += 6, offset += 4) {
            indices32UI[i + 0] = offset + 0;
            indices32UI[i + 1] = offset + 1;
            indices32UI[i + 2] = offset + 2;

            indices32UI[i + 3] = offset + 0;
            indices32UI[i + 4] = offset + 2;
            indices32UI[i + 5] = offset + 3;
        }

        // vertex array
        quadVertexArray = VertexArray::create();
        quadVertexArray->setVertexBuffer(quadVertexBuffer);
        quadVertexArray->setIndexBuffer(IndexBufferUI32::create(indices32UI, maxIndexCount));

        // assuming imidiate upload to GPU
        delete[] indices32UI;

        textureSlots = new Ref<Texture2D>[(uint32_t)maxTextureSlots];

        this->reset();
    }

    RendererData2D::~RendererData2D() {
        // release if owned
        if ( !quadVertexBuffer->getCPUStorage() ) delete[] vertexData;
        delete[] textureSlots;
    }

    void RendererData2D::reset() {
        vertexDataPtr = vertexData;
        curIndexCount = 0;
        curTextureID = 1; // 0 is reserved for white texture
    }

    bool RendererData2D::shouldFlush() {
        if ( curIndexCount == maxIndexCount ||
             curTextureID  == maxTextureSlots ) {
            return true;
        }
        return false;
    }
}
