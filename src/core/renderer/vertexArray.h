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
        virtual void addVertexBuffer(const Ref<VertexBuffer>& vertexBuffer) = 0;
        virtual void setIndexBuffer(const Ref<IndexBuffer>& indexBuffer) = 0;
        inline  void setModelMat(const glm::mat4& mat) { _modelMat = mat; }

        inline const std::vector<Ref<VertexBuffer> >& getVertexBuffers() const { return _vertexBuffers; }
        inline const Ref<VertexBuffer>& getVertexBuffer(int index) const { return _vertexBuffers[index]; }
        inline const Ref<IndexBuffer>& getIndexBuffer() const { return _indexBuffer; }
        inline const glm::mat4& getModelMat() const { return _modelMat; }

        static Ref<VertexArray> create();
    protected:
        glm::mat4                         _modelMat;
        std::vector<Ref<VertexBuffer> >   _vertexBuffers;
        Ref<IndexBuffer>                  _indexBuffer;
    };
}

#endif /* __VERTEX_ARRAY_H__ */
