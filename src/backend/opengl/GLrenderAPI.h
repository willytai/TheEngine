#ifndef __GL_RENDER_H__
#define __GL_RENDER_H__

#include "core/renderer/renderAPI.h"
#include "backend/OpenGL/GLmacro.h"
#include "texture.h"
#include "camera.h"

namespace Engine7414
{
    class GLRenderAPI : public RenderAPI
    {
    public:
        ~GLRenderAPI() {}
        void clear() const override;
        void setClearColor(const glm::vec4& color) const override;
        void drawElement(const VertexArray* vertexArray) const override;
        RendererBackend backend() const override { return RendererBackend::OpenGL; }
    };
}

#endif /* __GL_RENDER_H__ */
