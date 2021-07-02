#ifndef __RENDERER_H__
#define __RENDERER_H__

#include "core/renderer/vertexArray.h"
#include "core/renderer/buffer.h"
#include "core/renderer/shader.h"
#include "core/renderer/renderCommands.h"
#include "core/renderer/frameBuffer.h"
#include "core/renderer/rendererData.h"
#include "core/event/event.h"
#include "backend/backend.h"
#include "editor/editorCamera.h"


namespace Engine7414
{
    class Renderer
    {
        // all global uniforms
        enum GUniform
        {
            G_UNIFORM_PROJ_VIEW_MAT = 0, // the view projection matrix
            G_UNIFORM_CAMERA_POS = 1,    // the position of the camera
        };
        static std::vector<UniformHandle>   _globalUniformHandle;
        
        struct sceneData {
            glm::mat4 ProjViewMat;
        };
        static sceneData __data__;
        static bool __updateProjViewMat__;

    public:
        static void setUpdateMatFlag();

        static void init(RendererBackend backend);
        static void shutdown();

        static void beginScene(Ref<EditorCamera>& camera, const Ref<FrameBuffer>& currentFrameBuffer);
        static void endScene();
        static void flush();

        static RendererData::statistics stat();

    public:
        // cube
        static void drawCube(const glm::mat4& transform, const glm::vec4& color);
        static void drawCube(const glm::mat4& transform, const glm::vec4& color, int enttID);

    public:
        static void setMaxTextSlot(const int& maxSlot);
    
    public:
        static ShaderLibrary& getShaderDict() { return ShaderLibrary::get(); }
        static RendererBackend backend() { return RenderCommands::getBackend(); }

    private:
        static void registerGlobalUniform();
    };
}

#endif /* __RENDERER_H__ */
