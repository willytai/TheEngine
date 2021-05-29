#include "backend/MTL/MTLbuffer.h"
#include "backend/MTL/MTLcontext.h"

#import "backend/MTL/MTLdataType.h"

namespace Engine7414
{
    uint32_t MTLVertexBuffer::indexCount = 0;

    MTLVertexBuffer::MTLVertexBuffer(size_t size) {
        // TODO only managed buffers are avaiable for now
        //      might wanna add interfaces for generation of buffers of different types
        _handle = [[MTLVertexBufferHandle alloc] initWithSize:size From:MTLContext::getContext().nativeDevice];
        _bufferIndex = indexCount++;
    }

    MTLVertexBuffer::MTLVertexBuffer(size_t size, uint32_t index) {
        _handle = [[MTLVertexBufferHandle alloc] initWithSize:size From:MTLContext::getContext().nativeDevice];
        CORE_ASSERT( index >= indexCount, "buffer index {} already taken" );
        _bufferIndex = index;
        indexCount = index+1;
    }

    MTLVertexBuffer::MTLVertexBuffer(const void* vertices, size_t size) {
        CORE_ASSERT( false, "" );
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

#define MTLIndexBufferClassImpl( baseName, dtype) \
    MTL##baseName::MTL##baseName(const dtype* data, uint32_t count) { \
        CORE_INFO( "using data type: {}", #dtype); \
        toMetalIndexType(this->type()); \
        _handle = [[MTLIndexBufferHandle alloc] initWithBytes:(const void*)data \
                                                       Length:sizeof(dtype)*count \
                                                         From:MTLContext::getContext().nativeDevice]; \
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

    MTLIndexBufferClassImpl( IndexBufferUI8, uint8_t )
    MTLIndexBufferClassImpl( IndexBufferUI32, uint32_t )
}
