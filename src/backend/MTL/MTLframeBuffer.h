#ifndef __MTL_FRAME_BUFFER_H__
#define __MTL_FRAME_BUFFER_H__

#include "core/renderer/frameBuffer.h"

#import "backend/MTL/MetalFrameBuffer.h"

namespace Engine7414
{
    class MTLFrameBuffer : public FrameBuffer
    {
    public:
        MTLFrameBuffer(const FrameBufferSpec& spec);
        ~MTLFrameBuffer();

        void bind() const override;
        void unbind() const override;
        void resize(const uint32_t& width, const uint32_t& height) override;
        void* colorAttachmentID() const override;
        const FrameBufferSpec& spec() const override { return _spec; }

    private:
        void regenerate();

    private:
        MTLFrameBufferHandle* _handle;

        FrameBufferSpec  _spec;
    };
}

#endif /* __MTL_FRAME_BUFFER_H__ */
