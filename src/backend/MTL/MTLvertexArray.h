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
        void setVertexBuffer(const Ref<VertexBuffer>& vertexBuffer) override;
        void setIndexBuffer(const Ref<IndexBuffer>& indexBuffer) override;

    private:
        // Thoughts
        // TODO store a vertexDescriptor, when bind is called, maybe hand over the ownerwhip of the descriptor to the renderAPI
        //      and check if the handle is the same inside the API, if not create a new state
    };

}

#endif /* __MTL_VERTEX_ARRAY_H__ */
