#ifndef __GL_VERTEX_ARRAY_H__
#define __GL_VERTEX_ARRAY_H__

#include "core/renderer/vertexArray.h"
#include "backend/OpenGL/GLmacro.h"
#include "backend/OpenGL/GLbuffer.h"
#include "backend/backend.h"
#include <vector>

namespace Engine7414
{

    class GLVertexArray : public VertexArray
    {
    public:
        GLVertexArray();
        ~GLVertexArray();

        void bind() const override;
        void unbind() const override;
        void addVertexBuffer(const VertexBuffer* vertexBuffer) override;
        void setIndexBuffer(const IndexBuffer* indexBuffer) override;

    private:
        GLuint  _rendererID;
        GLuint  _attrIndex;
    };

}

#endif /* __GL_VERTEX_ARRAY_H__ */
