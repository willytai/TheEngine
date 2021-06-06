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
        uint32_t colorAttachmentID(int index = 0) const override { return (uint32_t)_colorAttachmentsIDs[index]; }
        void readPixel(int x, int y, void* data, int index = 0) const override;
        const FrameBufferSpec& spec() const override { return _spec; }

        void clear() const override;

    // utility functions
    public:
        static void attachColorTexture(GLuint textureID, GLenum internalFormat, uint32_t sample, uint32_t width, uint32_t height, uint32_t index, GLenum accessFormat);
        static void attachDepthTexture(GLuint textureID, GLenum internalFormat, uint32_t sample, uint32_t width, uint32_t height, GLenum attachmentType);
        static GLenum getTextureTarget(bool multiSample);

    private:
        void regenerate();

    private:
        GLuint              _rendererID;
        GLuint              _depthAttachmentID = 0;
        std::vector<GLuint> _colorAttachmentsIDs;
    };
}

#endif /* __GL_FRAME_BUFFER_H__ */
