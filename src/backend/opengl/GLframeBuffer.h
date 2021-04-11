#ifndef __GL_FRAME_BUFFER_H__
#define __GL_FRAME_BUFFER_H__

#include "core/renderer/frameBuffer.h"
#include "backend/OpenGL/GLmacro.h"

namespace Engine7414
{
    class GLFrameBuffer : public FrameBuffer
    {
    public:
        GLFrameBuffer(const FrameBufferSpec& spec);
        ~GLFrameBuffer();

        void bind() const override;
        void unbind() const override;
        void resize(const uint32_t& width, const uint32_t& height) override;
        uint32_t colorAttachmentID() const override { return (uint32_t)_colorAttachmentID; }
        const FrameBufferSpec& spec() const override { return _spec; }

    private:
        void regenerate();

    private:
        GLuint _rendererID;
        GLuint _colorAttachmentID;  // the sample-able color buffer
        GLuint _renderBufferID;     // for depth/stencil buffer

        FrameBufferSpec _spec;
    };
}

#endif /* __GL_FRAME_BUFFER_H__ */
