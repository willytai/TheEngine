#ifndef __MTL_VERTEX_ARRAY_H__
#define __MTL_VERTEX_ARRAY_H__

#include "core/renderer/vertexArray.h"
#include "backend/backend.h"
#include <vector>

namespace Engine7414
{

    class MTLVertexArray : public VertexArray
    {
    public:
        MTLVertexArray();
        ~MTLVertexArray();

        void bind() const override;
        void unbind() const override;
        void addVertexBuffer(const Ref<VertexBuffer>& vertexBuffer) override;
        void setIndexBuffer(const Ref<IndexBuffer>& indexBuffer) override;

    private:
    };

}

#endif /* __MTL_VERTEX_ARRAY_H__ */
