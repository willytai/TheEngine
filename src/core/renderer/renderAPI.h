#ifndef __RENDER_API__
#define __RENDER_API__

#include "glm/glm.hpp"
#include "core/renderer/vertexArray.h"
#include "backend/backend.h"

namespace Engine7414
{
    class RenderAPI
    {
    public:
        virtual ~RenderAPI() {}
        virtual void init() const = 0;
        virtual void setViewPort(const uint32_t& x, const uint32_t& y, const uint32_t& width, const uint32_t& height) const = 0;
        virtual void clear() const = 0;
        virtual void setClearColor(const glm::vec4& color) const = 0;
        virtual void drawElement(const Ref<VertexArray>& vertexArray, const uint32_t& indexCount = 0) const = 0;
        virtual RendererBackend backend() const = 0;

        // test
        virtual void begin() const {};
        virtual void end() const {};
    };
}

#endif /* __RENDER_API__ */
