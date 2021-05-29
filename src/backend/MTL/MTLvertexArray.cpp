#include "backend/MTL/MTLvertexArray.h"
#include "backend/MTL/MTLdataType.h"

namespace Engine7414
{
    MTLVertexArray::MTLVertexArray() 
    {
        _attrIndex = 0;
        _handle = nil;
    }

    MTLVertexArray::~MTLVertexArray() {
    }

    void MTLVertexArray::setVertexBuffer(const Ref<VertexBuffer>& vertexBuffer) {
        BACKEND_ASSERT( vertexBuffer->layout().elements().size(), "vertex buffer has no layout!" );
        BACKEND_ASSERT( !this->_vertexBuffer, "vertex buffer already set!" );

        _handle = [[MTLVertexArrayHandle alloc] init];

        const auto& layout = vertexBuffer->layout();
        for (const auto& element : layout.elements()) {
            [_handle setElementFormat:toMetalDataType(element)
                          BufferIndex:vertexBuffer->getID()
                               Offset:element.offset];
            [_handle setStride:layout.stride()];
        }

        this->_vertexBuffer = vertexBuffer;
    }

    void MTLVertexArray::setIndexBuffer(const Ref<IndexBuffer>& indexBuffer) {
        CORE_ASSERT( !this->_indexBuffer, "index buffer already set" );
        this->_indexBuffer = indexBuffer;
    }

    void MTLVertexArray::bind() const {
        // [NOTE] no need to do anything here
        //        things should be handled inside MTLRenderAPI::drawElement
        // CORE_ASSERT( false, "" );
    }

    void MTLVertexArray::unbind() const {
        CORE_ASSERT( false, "" );
    }

}
