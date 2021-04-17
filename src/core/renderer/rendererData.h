#ifndef __RENDERER_DATA_H__
#define __RENDERER_DATA_H__

#include "core/renderer/shader.h"
#include "core/renderer/vertexArray.h"
#include "core/renderer/buffer.h"
#include "core/renderer/texture.h"
#include "core/renderer/renderer.h"
#include "glm/glm.hpp"

namespace Engine7414
{
    struct Vertex2D
    {
        glm::vec3   position;
        glm::vec4   color;
        glm::vec2   texCoor;
        float       samplerID; // int can't be interpolated by the fragment shader
    };

    struct RendererData2D
    {
        static glm::vec4 unitQuadVertices[4];
        static glm::vec2 textureCoords[4];
        static int maxTextureSlots;
        static void setMaxTextSlot(const int& n) { maxTextureSlots = n; }

        RendererData2D();
        ~RendererData2D();

        void reset();
        bool shouldFlush();

        const uint32_t maxQuadCount = 10000;
        const uint32_t maxIndexCount = maxQuadCount * 6;
        const uint32_t maxVertexCount = maxQuadCount * 4;

        // keeping it on the heap just in case maxQuadQount is set too big
        Vertex2D*   vertexData;
        Vertex2D*   vertexDataPtr;

        Ref<Shader>         textureShader;
        Ref<Texture2D>*     textureSlots;     // keeping on heap since maxTextureSlots needs to be queried during runtime
        Ref<VertexBuffer>   quadVertexBuffer;
        Ref<VertexArray>    quadVertexArray;

        uint32_t    curIndexCount;
        int         curTextureID;

        Renderer2D::statistics  stats;
    };
}

#endif
