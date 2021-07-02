#include "backend/OpenGL/GLframeBuffer.h"

namespace Engine7414
{
    // utility functions
    GLenum GLFrameBuffer::getTextureTarget(bool multiSample) {
        return multiSample ? GL_TEXTURE_2D_MULTISAMPLE : GL_TEXTURE_2D;
    }

    void GLFrameBuffer::attachColorTexture(GLuint textureID, GLenum internalFormat, uint32_t sample, uint32_t width, uint32_t height, uint32_t index, GLenum accessFormat) {
        auto textureTarget = GLFrameBuffer::getTextureTarget(sample > 1);
        if (textureTarget == GL_TEXTURE_2D) {
            GLCall( glTexImage2D(GL_TEXTURE_2D, 0, internalFormat, width, height, 0, accessFormat, GL_UNSIGNED_BYTE, nullptr) );
            GLCall( glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR) );
            GLCall( glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR) );
            GLCall( glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE) );
            GLCall( glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE) );
            GLCall( glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE) );
        }
        else {
            GLCall( glTexImage2DMultisample(GL_TEXTURE_2D_MULTISAMPLE, sample, internalFormat, width, height, GL_FALSE) );
        }

        GLCall( glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + index, textureTarget, textureID, 0));
    }

    void GLFrameBuffer::attachDepthTexture(GLuint textureID, GLenum internalFormat, uint32_t sample, uint32_t width, uint32_t height, GLenum attachmentType) {
        if (sample > 1) {
            GLCall( glRenderbufferStorageMultisample(GL_RENDERBUFFER, sample, internalFormat, width, height) );
        }
        else {
            GLCall( glRenderbufferStorage(GL_RENDERBUFFER, internalFormat, width, height) );
        }

        GLCall( glFramebufferRenderbuffer(GL_FRAMEBUFFER, attachmentType, GL_RENDERBUFFER, textureID) );
    }

    GLFrameBuffer::GLFrameBuffer(const FrameBufferSpec& spec) :
        FrameBuffer(spec),
        _rendererID(0),
        _depthAttachmentID(0)
    {
        this->regenerate();
    }

    GLFrameBuffer::~GLFrameBuffer() {
        GLCall( glDeleteFramebuffers(1, &_rendererID) );
        GLCall( glDeleteTextures((GLsizei)_colorAttachmentsIDs.size(), _colorAttachmentsIDs.data()) );
        GLCall( glDeleteRenderbuffers(1, &_depthAttachmentID) );
    }

    void GLFrameBuffer::regenerate() {
        if (_rendererID) {
            GLCall( glDeleteFramebuffers(1, &_rendererID) );
            GLCall( glDeleteTextures((GLsizei)_colorAttachmentsIDs.size(), _colorAttachmentsIDs.data()) );
            GLCall( glDeleteRenderbuffers(1, &_depthAttachmentID) );

            _colorAttachmentsIDs.clear();
            _depthAttachmentID = _rendererID = 0;
        }

        // frame buffer
        GLCall( glGenFramebuffers(1, &_rendererID) );
        GLCall( glBindFramebuffer(GL_FRAMEBUFFER, _rendererID) );

        GLenum textureTarget = GLFrameBuffer::getTextureTarget(_spec.sample > 1);
        
        // color attachments
        if (_colorAttachmentDescs.size()) {
            _colorAttachmentsIDs.resize(_colorAttachmentDescs.size());

            // regenerate all the textures
            GLCall( glCreateTextures(textureTarget, (GLsizei)_colorAttachmentsIDs.size(), _colorAttachmentsIDs.data()) );

            // bind and set all the specs
            for (uint32_t i = 0; i < _colorAttachmentsIDs.size(); ++i) {
                const auto& textureID = _colorAttachmentsIDs[i];
                const auto& textureDecs = _colorAttachmentDescs[i];
                GLCall( glBindTexture(textureTarget, textureID) );
                switch (textureDecs.format) {
                    case FrameBufferTextureFormat::RGBA8:   GLFrameBuffer::attachColorTexture(textureID, GL_RGBA8, _spec.sample, _spec.width, _spec.height, i, GL_RGBA); break;
                    case FrameBufferTextureFormat::RED_INT: GLFrameBuffer::attachColorTexture(textureID, GL_R32I, _spec.sample, _spec.width, _spec.height, i, GL_RED_INTEGER); break;
                    default: CORE_ERROR("unsupported frame buffer texture format");
                }
            }
        }

        // depth attachment
        if (_depthAttachmentDesc.format != FrameBufferTextureFormat::UNDEF) {
            GLCall( glCreateRenderbuffers(1, &_depthAttachmentID) );
            GLCall( glBindRenderbuffer(GL_RENDERBUFFER, _depthAttachmentID) );
            switch (_depthAttachmentDesc.format) {
                case FrameBufferTextureFormat::DEPTH24STENCIL8: GLFrameBuffer::attachDepthTexture(_depthAttachmentID, GL_DEPTH24_STENCIL8, _spec.sample, _spec.width, _spec.height, GL_DEPTH_STENCIL_ATTACHMENT); break;
                default: CORE_ERROR("unsupported frame buffer texture format");
            }
        }

        // need to enable the color attchments if more than 1 is requested
        if (_colorAttachmentsIDs.size() > 1) {
            CORE_ASSERT( _colorAttachmentsIDs.size() <= 4, "a maximum of 4 color attchments per framebuffer is supported for now" );
            static GLenum attachments[4] = { GL_COLOR_ATTACHMENT0, GL_COLOR_ATTACHMENT1, GL_COLOR_ATTACHMENT2, GL_COLOR_ATTACHMENT3 };
            GLCall( glDrawBuffers((GLsizei)_colorAttachmentsIDs.size(), attachments) );
        }
        // only depth
        else if (_colorAttachmentsIDs.empty()) {
            GLCall( glDrawBuffer(GL_NONE) );
        }

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

    void GLFrameBuffer::readPixel(int x, int y, void* data, int index) const {
        GLCall( glReadBuffer(GL_COLOR_ATTACHMENT0 + index) );
        GLCall( glReadPixels(x, y, 1, 1, GL_RED_INTEGER, GL_INT, data) );
    }

    void GLFrameBuffer::clear() const {
        // clear color attachments
        for (uint32_t index = 0; index < _colorAttachmentDescs.size(); ++index) {
            const auto& desc = _colorAttachmentDescs[index];
            if (desc.clearAction == FrameBufferTextureClearAction::DONT_CARE) continue;
            switch (desc.clearAction) {
                case FrameBufferTextureClearAction::CLEAR_AS_COLOR: GLCall(glClearBufferfv(GL_COLOR, index, &desc.clearData.color4.r)); break;
                case FrameBufferTextureClearAction::CLEAR_AS_INT:   GLCall(glClearBufferiv(GL_COLOR, index, &desc.clearData.int1)); break;
                default: CORE_ERROR("fuck");
            }
        }

        // clear depth
        if (_depthAttachmentDesc.format != FrameBufferTextureFormat::UNDEF &&
            _depthAttachmentDesc.clearAction != FrameBufferTextureClearAction::DONT_CARE) {
            switch (_depthAttachmentDesc.format) {
            case FrameBufferTextureFormat::DEPTH24STENCIL8: GLCall(glClearBufferfi(GL_DEPTH_STENCIL, 0, _depthAttachmentDesc.clearData.fi.f, _depthAttachmentDesc.clearData.fi.i)); break;
                default: CORE_ERROR("fuck");
            }
        }
    }
}
