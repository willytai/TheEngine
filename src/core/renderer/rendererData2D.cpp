#include "core/renderer/rendererData2D.h"

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
        textureSlots = new Ref<Texture2D>[(uint32_t)maxTextureSlots];
        vertexData = new Vertex2D[maxVertexCount];
        this->reset();
    }

    RendererData2D::~RendererData2D() {
        delete[] vertexData;
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
