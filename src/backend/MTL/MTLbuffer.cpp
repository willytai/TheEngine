#include "backend/MTL/MTLbuffer.h"
#include "backend/MTL/MTLcontext.h"

namespace Engine7414
{

    MTLVertexBuffer::MTLVertexBuffer(size_t size) {
        // TODO only managed buffers are avaiable for now
        //      might wanna add interfaces for generation of buffers of different types
        _handle = [[MTLVertexBufferHandle alloc] initWithSize:size From:MTLContext::getContext().nativeDevice];
    }

    MTLVertexBuffer::MTLVertexBuffer(const void* vertices, size_t size) {
    }

    MTLVertexBuffer::~MTLVertexBuffer() {
    }

    void MTLVertexBuffer::bind() const {
        CORE_ASSERT( false, "" );
    }

    void MTLVertexBuffer::unbind() const {
        CORE_ASSERT( false, "" );
    }

    void* MTLVertexBuffer::getCPUStorage() const {
        return _handle.buffer.contents;
    }

    void MTLVertexBuffer::setData(const void* data, const size_t& size) {
        CORE_ASSERT( _handle.buffer.contents == data,
                     "location of the data on the system storage needs to be queried from the Metal buffer, don't allocate it yourself!" );
        [_handle syncGPUWithCPU:size];
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
