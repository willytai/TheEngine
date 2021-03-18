#ifndef __RENDER_COMMANDS_H__
#define __RENDER_COMMANDS_H__

#include "backend/backend.h"
#include "core/renderer/renderAPI.h"

namespace Engine7414
{
    class RenderCommands
    {
        static Scoped<RenderAPI> __backend__;
    public:
        static void setBackend(RendererBackend backend);
        static RendererBackend getBackend();

        static void clear();
        static void clear(const glm::vec4& color);
        static void drawElement(const Ref<VertexArray>& vertexArray);
    };
}

#endif /* __RENDER_COMMANDS_H__ */
