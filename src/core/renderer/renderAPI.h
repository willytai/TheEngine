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
        virtual void clear() const = 0;
        virtual void setClearColor(const glm::vec4& color) const = 0;
        virtual void drawElement(const Ref<VertexArray>& vertexArray) const = 0;
        virtual RendererBackend backend() const = 0;
    };
}

#endif /* __RENDER_API__ */
