#ifndef __MTL_BUFFER_H__
#define __MTL_BUFFER_H__

#include "core/renderer/buffer.h"

#import "backend/MTL/MetalBuffer.h"

namespace Engine7414
{

    class MTLVertexBuffer : public VertexBuffer
    {
    public:
        MTLVertexBuffer(size_t size);
        MTLVertexBuffer(const void* vertices, size_t size);
        ~MTLVertexBuffer();

        void bind() const override;
        void unbind() const override;

        void* getCPUStorage() const override;
        void setData(const void* data, const size_t& size) override;

    private:
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
    private: \
    }

    MTLIndexBufferClass( IndexBufferUI8,  uint8_t );
    MTLIndexBufferClass( IndexBufferUI32, uint32_t );
}
#endif /* __MTL_BUFFER_H__ */
