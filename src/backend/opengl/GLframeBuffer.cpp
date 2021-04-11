#include "backend/OpenGL/GLframeBuffer.h"

namespace Engine7414
{
    GLFrameBuffer::GLFrameBuffer(const FrameBufferSpec& spec) :
        _rendererID(0),
        _colorAttachmentID(0),
        _renderBufferID(0),
        _spec(spec)
    {
        this->regenerate();
    }

    GLFrameBuffer::~GLFrameBuffer() {
        GLCall( glDeleteFramebuffers(1, &_rendererID) );
        GLCall( glDeleteTextures(1, &_colorAttachmentID) );
        GLCall( glDeleteRenderbuffers(1, &_renderBufferID) );
    }

    void GLFrameBuffer::regenerate() {
        if ( _rendererID == 0 ) GLCall( glDeleteFramebuffers(1, &_rendererID) );
        if ( _colorAttachmentID == 0 ) GLCall( glDeleteTextures(1, &_colorAttachmentID) );
        if ( _renderBufferID == 0 ) GLCall( glDeleteRenderbuffers(1, &_renderBufferID) );

        // frame buffer
        GLCall( glGenFramebuffers(1, &_rendererID) );
        GLCall( glBindFramebuffer(GL_FRAMEBUFFER, _rendererID) );

        // color attachment, using texture image to make it sample-able
        GLCall( glGenTextures(1, &_colorAttachmentID) );
        GLCall( glBindTexture(GL_TEXTURE_2D, _colorAttachmentID) );
        GLCall( glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, _spec.width, _spec.height, 0, GL_RGBA, GL_UNSIGNED_BYTE, 0) );
        GLCall( glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR) );
        GLCall( glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR) );
        GLCall( glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, _colorAttachmentID, 0) );

        // depth/stencil buffers are not meant to be sampled, creating them via render buffer
        GLCall( glGenRenderbuffers(1, &_renderBufferID) );
        GLCall( glBindRenderbuffer(GL_RENDERBUFFER, _renderBufferID) );
        GLCall( glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, _spec.width, _spec.height) );
        GLCall( glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, _renderBufferID) );

        // check
        if ( glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE ) {
            BACKEND_ASSERT( false, "framebuffer not complete!" );
        }

        // explicitly bind frame buffers if you want to use them
        GLCall( glBindFramebuffer(GL_FRAMEBUFFER, 0) );

        // if the target view port is resized, the frame buffer will (needs to) be regenerated, so
        // we only have to set the viewport once here instead of doing it on each bind call
        GLCall( glViewport( 0, 0, (GLsizei)_spec.width, (GLsizei)_spec.height ) );
    }

    void GLFrameBuffer::bind() const {
        GLCall( glBindFramebuffer(GL_FRAMEBUFFER, _rendererID) );
    }

    void GLFrameBuffer::unbind() const {
        GLCall( glBindFramebuffer(GL_FRAMEBUFFER, 0) );
    }

    void GLFrameBuffer::resize(const uint32_t& width, const uint32_t& height) {
        _spec.width = width;
        _spec.height = height;
        this->regenerate();
    }
}
