#include "core/renderer/rendererData.h"

namespace Engine7414
{
    int RendererData2D::maxTextureSlots = 0;

    RendererData2D::RendererData2D() {
        CORE_ASSERT( maxTextureSlots > 0, "maximum texture slots not set before renderer initialization!" );
        textureSlots = new Ref<Texture2D>[(uint32_t)maxTextureSlots];
        vertexData = new Vertex2D[maxVertexCount];
        vertexDataPtr = vertexData;
        curIndexCount = 0;
        curTextureID = 1; // 0 is reserved for white texture
    }

    RendererData2D::~RendererData2D() {
        delete[] vertexData;
        delete[] textureSlots;
    }

    void RendererData2D::reset() {
        vertexDataPtr = vertexData;
        curIndexCount = 0;
        curTextureID = 1;
    }

    bool RendererData2D::shouldFlush() {
        if ( curIndexCount == maxIndexCount ||
             curTextureID  == maxTextureSlots ) {
            return true;
        }
        return false;
    }
}
