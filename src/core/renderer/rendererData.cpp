#include "core/renderer/rendererData.h"

namespace Engine7414
{
    std::array<RendererData::VertexTemplate, 24> RendererData::unitCubeVerticesWithNormals;

    void RendererData::fillCubeData() {
        // cube with normals
        // counterclockwise
        // front -> right -> back -> left -> top -> bottom
        unitCubeVerticesWithNormals = { {
            {{-0.5f, -0.5f,  0.5f}, { 0.0f,  0.0f,  1.0f}},
            {{ 0.5f, -0.5f,  0.5f}, { 0.0f,  0.0f,  1.0f}},
            {{ 0.5f,  0.5f,  0.5f}, { 0.0f,  0.0f,  1.0f}},
            {{-0.5f,  0.5f,  0.5f}, { 0.0f,  0.0f,  1.0f}},

            {{ 0.5f, -0.5f,  0.5f}, { 1.0f,  0.0f,  0.0f}},
            {{ 0.5f, -0.5f, -0.5f}, { 1.0f,  0.0f,  0.0f}},
            {{ 0.5f,  0.5f, -0.5f}, { 1.0f,  0.0f,  0.0f}},
            {{ 0.5f,  0.5f,  0.5f}, { 1.0f,  0.0f,  0.0f}},

            {{ 0.5f, -0.5f, -0.5f}, { 0.0f,  0.0f, -1.0f}},
            {{-0.5f, -0.5f, -0.5f}, { 0.0f,  0.0f, -1.0f}},
            {{-0.5f,  0.5f, -0.5f}, { 0.0f,  0.0f, -1.0f}},
            {{ 0.5f,  0.5f, -0.5f}, { 0.0f,  0.0f, -1.0f}},

            {{-0.5f, -0.5f, -0.5f}, {-1.0f,  0.0f,  0.0f}},
            {{-0.5f, -0.5f,  0.5f}, {-1.0f,  0.0f,  0.0f}},
            {{-0.5f,  0.5f,  0.5f}, {-1.0f,  0.0f,  0.0f}},
            {{-0.5f,  0.5f, -0.5f}, {-1.0f,  0.0f,  0.0f}},

            {{-0.5f,  0.5f,  0.5f}, { 0.0f,  1.0f,  0.0f}},
            {{ 0.5f,  0.5f,  0.5f}, { 0.0f,  1.0f,  0.0f}},
            {{ 0.5f,  0.5f, -0.5f}, { 0.0f,  1.0f,  0.0f}},
            {{-0.5f,  0.5f, -0.5f}, { 0.0f,  1.0f,  0.0f}},

            {{-0.5f, -0.5f,  0.5f}, { 0.0f, -1.0f,  0.0f}},
            {{ 0.5f, -0.5f,  0.5f}, { 0.0f, -1.0f,  0.0f}},
            {{ 0.5f, -0.5f, -0.5f}, { 0.0f, -1.0f,  0.0f}},
            {{-0.5f, -0.5f, -0.5f}, { 0.0f, -1.0f,  0.0f}}
        } };
    }
    
    void RendererData::fillObjectData() {
        RendererData::fillCubeData();
    }

    RendererData::RendererData() {
        // CPU memory
        vertexData = new Vertex3D[maxVertexCount];
        
        // GPU memory
        // vertices
        vertexBuffer = VertexBuffer::create(maxVertexCount * sizeof(Vertex3D));
        vertexBuffer->setLayout(
            {
                {BufferDataType::Float, 3}, // position
                {BufferDataType::Float, 3}, // normal
                {BufferDataType::Float, 4}, // color
                {BufferDataType::Int,   1}  // entity ID
            }
        );
        // indices
        uint32_t* indices = new uint32_t[maxIndexCount];
        for (int i = 0, offset = 0; i < maxIndexCount; i += 36, offset += 24) {
            for (int face = 0, idOffset = 0; face < 6*6; face += 6, idOffset += 4) {
                indices[i + face + 0] = offset + idOffset + 0;
                indices[i + face + 1] = offset + idOffset + 1;
                indices[i + face + 2] = offset + idOffset + 2;

                indices[i + face + 3] = offset + idOffset + 0;
                indices[i + face + 4] = offset + idOffset + 2;
                indices[i + face + 5] = offset + idOffset + 3;
            }
            // // front
            // indices[i + 0] = offset + 0;
            // indices[i + 1] = offset + 1;
            // indices[i + 2] = offset + 2;
            // 
            // indices[i + 3] = offset + 0;
            // indices[i + 4] = offset + 2;
            // indices[i + 5] = offset + 3;
            // // right
            // indices[i + 6] = offset + 4;
            // indices[i + 7] = offset + 5;
            // indices[i + 8] = offset + 6;
            // 
            // indices[i + 9]  = offset + 4;
            // indices[i + 10] = offset + 6;
            // indices[i + 11] = offset + 7;
            // // back
            // indices[i + 12] = offset + 8;
            // indices[i + 13] = offset + 9;
            // indices[i + 14] = offset + 10;
            // 
            // indices[i + 15] = offset + 8;
            // indices[i + 16] = offset + 10;
            // indices[i + 17] = offset + 11;
            // // left
            // indices[i + 18] = offset + 12;
            // indices[i + 19] = offset + 13;
            // indices[i + 20] = offset + 14;
            // 
            // indices[i + 21] = offset + 12;
            // indices[i + 22] = offset + 14;
            // indices[i + 23] = offset + 15;
            // // top
            // indices[i + 24] = offset + 16;
            // indices[i + 25] = offset + 17;
            // indices[i + 26] = offset + 18;
            // 
            // indices[i + 27] = offset + 16;
            // indices[i + 28] = offset + 18;
            // indices[i + 29] = offset + 19;
            // // bottom
            // indices[i + 30] = offset + 20;
            // indices[i + 31] = offset + 21;
            // indices[i + 32] = offset + 22;
            // 
            // indices[i + 33] = offset + 20;
            // indices[i + 34] = offset + 22;
            // indices[i + 35] = offset + 23;
        }
        // vertex array
        vertexArray = VertexArray::create();
        vertexArray->addVertexBuffer(vertexBuffer);
        vertexArray->setIndexBuffer(IndexBufferUI32::create(indices, maxIndexCount));
        
        // assuming imediate upload
        delete[] indices;

        // populate the macros
        fillObjectData();

        // general stuffs
        this->reset();
    }

    RendererData::~RendererData() {
        delete[] vertexData;
    }

    void RendererData::reset() {
        vertexDataPtr = vertexData;
        totalIndexCount = 0;
        stats.reset();
    }

    bool RendererData::shouldFlush() {
        if (stats.vertices == maxVertexCount ||
            totalIndexCount == maxIndexCount) return true;
        return false;
    }

}