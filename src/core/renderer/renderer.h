#ifndef __RENDERER_H__
#define __RENDERER_H__

#include "core/renderer/vertexArray.h"
#include "core/renderer/buffer.h"
#include "core/renderer/shader.h"
#include "core/renderer/renderCommands.h"
#include "core/renderer/camera.h"
#include "backend/backend.h"

namespace Engine7414
{
    class Renderer
    {
        struct sceneData {
            glm::mat4 ProjViewMat;
        };
        static sceneData __data__;
    public:
        static void beginScene(const Camera& camera, const glm::vec4& color = {0.0f, 0.0f, 0.0f, 1.0f});
        static void submit(const Ref<Shader>& shader, const Ref<VertexArray>& vertexArray);
        static void endScene();

        static ShaderDict& getShaderDict() { return ShaderDict::get(); }

        static void init(RendererBackend backend);
        static RendererBackend backend() { return RenderCommands::getBackend(); }
    };
}

#endif /* __RENDERER_H__ */
