#ifndef __FRAME_BUFFER_H__
#define __FRAME_BUFFER_H__

#include "core/core.h"

namespace Engine7414
{
    struct FrameBufferSpec
    {
        uint32_t width;
        uint32_t height;
    };

    class FrameBuffer
    {
    public:
        FrameBuffer() = default;
        virtual ~FrameBuffer() = default;

        virtual void bind() const = 0;
        virtual void unbind() const = 0;
        virtual void resize(const uint32_t& width, const uint32_t& height) = 0;
        virtual void* colorAttachmentID() const = 0;
        virtual const FrameBufferSpec& spec() const = 0;

        static Ref<FrameBuffer> create(const FrameBufferSpec& spec);
    };
}

#endif /* __FRAME_BUFFER_H__ */
