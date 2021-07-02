#ifndef __RENDERER_DATA_H__
#define __RENDERER_DATA_H__

#include "core/renderer/shader.h"
#include "core/renderer/vertexArray.h"
#include "core/renderer/buffer.h"
#include "core/renderer/texture.h"

#include <glm/glm.hpp>

namespace Engine7414
{
    // not supporting textures for now
    struct Vertex3D
    {
        glm::vec3   position;
        glm::vec3   normal;
        glm::vec4   color;

        // for the editor
        int         entityID;
    };

    struct RendererData
    {
        RendererData();
        ~RendererData();
    
        void reset();
        bool shouldFlush();

        const uint32_t maxVertexCount = 100000;
        const uint32_t maxIndexCount = 100000 / 24 * 36;

        Vertex3D*    vertexData;
        Vertex3D*    vertexDataPtr;

        // the phong shader
        Ref<Shader>  phongShader;

        // handle to the GPU memory
        Ref<VertexBuffer> vertexBuffer;
        Ref<VertexArray>  vertexArray;

        uint32_t totalIndexCount = 0;

        struct statistics
        {
            uint32_t drawCalls = 0;
            uint32_t vertices = 0;

            void reset() { drawCalls = vertices = 0; }
        } stats;


        friend class Renderer;
    private:
        struct VertexTemplate
        {
            glm::vec3 position;
            glm::vec3 normal;
        };
        static std::array<VertexTemplate, 24> unitCubeVerticesWithNormals;
        static void fillObjectData();
        static void fillCubeData();
    };
}

#endif