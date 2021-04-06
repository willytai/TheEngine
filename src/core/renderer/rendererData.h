#ifndef __RENDERER_DATA_H__
#define __RENDERER_DATA_H__

#include "core/renderer/shader.h"
#include "core/renderer/vertexArray.h"
#include "core/renderer/buffer.h"
#include "core/renderer/texture.h"
#include "glm/glm.hpp"

namespace Engine7414
{
    struct Vertex2D
    {
        glm::vec3    position;
        glm::vec4   color;
        glm::vec2    texCoor;
    };

    struct RendererData2D
    {
        RendererData2D();
        ~RendererData2D();

        void reset();

        const uint32_t maxQuadCount = 10000;
        const uint32_t maxIndexCount = maxQuadCount * 6;
        const uint32_t maxVertexCount = maxQuadCount * 4;

        // keeping it on the heap just in case maxQuadQount is set too big
        Vertex2D*        vertexData;
        Vertex2D*        vertexDataPtr;
        uint32_t        curIndexCount;

        Ref<Shader>            textureShader;
        Ref<VertexBuffer>    quadVertexBuffer;
        Ref<VertexArray>    quadVertexArray;
        Ref<Texture2D>        whiteTexture;
    };
}

#endif
