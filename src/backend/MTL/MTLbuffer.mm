#include "backend/MTL/MTLbuffer.h"

namespace Engine7414
{

    MTLVertexBuffer::MTLVertexBuffer(size_t size) {
    }

    MTLVertexBuffer::MTLVertexBuffer(const void* vertices, size_t size) {
    }

    MTLVertexBuffer::~MTLVertexBuffer() {
    }

    void MTLVertexBuffer::bind() const {
    }

    void MTLVertexBuffer::unbind() const {
    }

    void MTLVertexBuffer::setData(const void* data, const size_t& size) {
    }

#define MTLIndexBufferClassImpl( baseName, type) \
    MTL##baseName::MTL##baseName(const type* data, uint32_t count) { \
    } \
 \
    MTL##baseName::~MTL##baseName() { \
    } \
 \
    void MTL##baseName::bind() const { \
    } \
 \
    void MTL##baseName::unbind() const { \
    }

    MTLIndexBufferClassImpl( IndexBufferUI8,  uint8_t )
    MTLIndexBufferClassImpl( IndexBufferUI32, uint32_t )
}
