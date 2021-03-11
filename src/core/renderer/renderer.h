#ifndef __RENDERER_H__
#define __RENDERER_H__

#include "core/renderer/vertexArray.h"
#include "core/renderer/buffer.h"
#include "core/renderer/shader.h"
#include "core/renderer/renderCommands.h"
#include "backend/backend.h"

namespace Engine7414
{
    class Renderer
    {
    public:
        static void beginScene(bool clear = false);
        static void beginScene(const glm::vec4& color);
        static void submit(const VertexArray* vertexArray);
        static void endScene();

        static void init(RendererBackend backend);
        static RendererBackend backend() { return RenderCommands::getBackend(); }
    };
}

#endif /* __RENDERER_H__ */
