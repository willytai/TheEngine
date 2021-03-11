#ifndef __VERTEX_ARRAY_H__
#define __VERTEX_ARRAY_H__

#include "core/renderer/buffer.h"

namespace Engine7414
{
    class VertexArray
    {
    public:
        VertexArray() {}
        virtual ~VertexArray() {}

        virtual void bind() const = 0;
        virtual void unbind() const = 0;
        virtual void addVertexBuffer(const VertexBuffer* vertexBuffer) = 0;
        virtual void setIndexBuffer(const IndexBuffer* indexBuffer) = 0;

        inline const std::vector<const VertexBuffer*>& getVertexBuffers() const { return _vertexBuffers; }
        inline const IndexBuffer* getIndexBuffer() const { return _indexBuffer; }

        static VertexArray* create();
    protected:
        std::vector<const VertexBuffer*>  _vertexBuffers;
        const IndexBuffer*                _indexBuffer;
    };
}

#endif /* __VERTEX_ARRAY_H__ */
