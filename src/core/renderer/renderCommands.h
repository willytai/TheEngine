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
        static RendererBackend getBackend();

        static void init(RendererBackend backend);
        static void setViewPort(const uint32_t& x, const uint32_t& y, const uint32_t& width, const uint32_t& height);
        static void clear();
        static void clear(const glm::vec4& color);
        static void drawElement(const Ref<VertexArray>& vertexArray, const uint32_t& indexCount = 0);

        // test
        static void begin();
        static void end();
    };
}

#endif /* __RENDER_COMMANDS_H__ */
