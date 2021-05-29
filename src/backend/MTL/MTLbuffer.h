#ifndef __MTL_BUFFER_H__
#define __MTL_BUFFER_H__

#include "core/renderer/buffer.h"

#import "backend/MTL/MetalBuffer.h"

namespace Engine7414
{

    class MTLVertexBuffer : public VertexBuffer
    {
        static uint32_t indexCount;
    public:
        MTLVertexBuffer(size_t size);
        MTLVertexBuffer(size_t size, uint32_t index);
        MTLVertexBuffer(const void* vertices, size_t size);
        ~MTLVertexBuffer();

        void bind() const override;
        void unbind() const override;

        uint32_t getID() const override { return _bufferIndex; }

        void* getCPUStorage() const override;
        void setData(const void* data, const size_t& size) override;

        // for internal use
        MTLVertexBufferHandle* getMetalHandle() const { return _handle; }

    private:
        uint32_t                _bufferIndex;
        MTLVertexBufferHandle*  _handle;
    };

#define MTLIndexBufferClass( baseName, type) \
    class MTL##baseName : public baseName \
    { \
    public: \
        MTL##baseName(const type* data, uint32_t count); \
        ~MTL##baseName(); \
 \
        void bind() const override; \
        void unbind() const override; \
 \
        MTLIndexBufferHandle* getMetalHandle() const { return _handle; } \
 \
    private: \
        MTLIndexBufferHandle*   _handle; \
    }

    MTLIndexBufferClass( IndexBufferUI8, uint8_t );
    MTLIndexBufferClass( IndexBufferUI32, uint32_t );
}
#endif /* __MTL_BUFFER_H__ */
