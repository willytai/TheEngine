#ifndef __VERTEX_ARRAY_H__
#define __VERTEX_ARRAY_H__

#include "glm/glm.hpp"
#include "core/renderer/buffer.h"

namespace Engine7414
{
    class VertexArray
    {
    public:
        VertexArray() : _modelMat(glm::mat4(1.0f)) {}
        virtual ~VertexArray() {}

        virtual void bind() const = 0;
        virtual void unbind() const = 0;
        virtual void setVertexBuffer(const Ref<VertexBuffer>& vertexBuffer) = 0;
        virtual void setIndexBuffer(const Ref<IndexBuffer>& indexBuffer) = 0;
        inline  void setModelMat(const glm::mat4& mat) { _modelMat = mat; }

        inline const Ref<VertexBuffer>& getVertexBuffers() const { return _vertexBuffer; }
        inline const Ref<IndexBuffer>& getIndexBuffer() const { return _indexBuffer; }
        inline const glm::mat4& getModelMat() const { return _modelMat; }

        static Ref<VertexArray> create();
    protected:
        glm::mat4           _modelMat;
        Ref<VertexBuffer>   _vertexBuffer;
        Ref<IndexBuffer>    _indexBuffer;
    };
}

#endif /* __VERTEX_ARRAY_H__ */
