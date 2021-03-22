#ifndef __GL_RENDER_H__
#define __GL_RENDER_H__

#include "core/renderer/renderAPI.h"
#include "backend/OpenGL/GLmacro.h"

namespace Engine7414
{
    class GLRenderAPI : public RenderAPI
    {
    public:
        ~GLRenderAPI() {}
        void init() const override;
        void clear() const override;
        void setClearColor(const glm::vec4& color) const override;
        void drawElement(const Ref<VertexArray>& vertexArray) const override;
        RendererBackend backend() const override { return RendererBackend::OpenGL; }
    };
}

#endif /* __GL_RENDER_H__ */
