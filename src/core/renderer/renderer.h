#ifndef __RENDERER_H__
#define __RENDERER_H__

#include "core/renderer/vertexArray.h"
#include "core/renderer/buffer.h"
#include "core/renderer/shader.h"
#include "core/renderer/renderCommands.h"
#include "core/renderer/camera.h"
#include "core/event/event.h"
#include "backend/backend.h"
#include "core/renderer/renderer2D.h"

namespace Engine7414
{
    class Renderer
    {
        struct sceneData {
            glm::mat4 ProjViewMat;
        };
        static sceneData __data__;
        static bool __updateProjViewMat__;
    public:
        static void setUpdateMatFlag();

        static void setMaxTextSlot(const int& maxSlot);

        static void init(RendererBackend backend);
        static void shutdown();

        static void onWindowResize(WindowResizeEvent& event);

        static void beginScene(const Ref<CameraBase>& camera, const glm::vec4& color = {0.0f, 0.0f, 0.0f, 1.0f});
        static void submit(const Ref<Shader>& shader, const Ref<VertexArray>& vertexArray);
        static void endScene();

        static ShaderDict& getShaderDict() { return ShaderDict::get(); }

        static RendererBackend backend() { return RenderCommands::getBackend(); }
    };
}

#endif /* __RENDERER_H__ */
