#include "backend/OpenGL/GLtexture.h"
#include <stb/stb_image.h>

namespace Engine7414
{
    GLTexture2D::GLTexture2D(const char* filepath)
        : _data(NULL), _rendererID(0),
        _width(0), _height(0), _bpp(0)
    {
        // load image
        stbi_set_flip_vertically_on_load(1);
        _data = stbi_load( filepath, &_width, &_height, &_bpp, 0 );
        BACKEND_VERIFY( _data, "stb_image: Failed to load {}", filepath );

#ifdef __APPLE__
        this->init_4_1();
#else
        this->init_4_5();
#endif

        // linear filtering for magnifying/minifying operations
        GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
        GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST));

        if (_data) stbi_image_free(_data);
    }

    GLTexture2D::~GLTexture2D() {
        GLCall(glDeleteTextures(1, &_rendererID));
    }

    void GLTexture2D::bind(uint32_t slot) const {
#ifdef __APPLE__
        GLCall(glActiveTexture(GL_TEXTURE0 + slot));
        GLCall(glBindTexture(GL_TEXTURE_2D, _rendererID));
#else
        GLCall(glBindTextureUnit(slot, _rendererID));
#endif
    }

    void GLTexture2D::unbind() const {
        GLCall(glBindTexture(GL_TEXTURE_2D, 0));
    }

    void GLTexture2D::init_4_1() {
        GLCall(glActiveTexture(GL_TEXTURE0));
        GLCall(glGenTextures(1, &_rendererID));
        GLCall(glBindTexture(GL_TEXTURE_2D, _rendererID));

        GLint  internalFormat = 0;
        GLenum dataFormat = 0;
        if ( _bpp == 4) {
            internalFormat = GL_RGBA8;
            dataFormat = GL_RGBA;
        }
        else if ( _bpp == 3) {
            internalFormat = GL_RGB8;
            dataFormat = GL_RGB;
        }
        BACKEND_ASSERT( internalFormat&&dataFormat, "unsupported file type when loading texture!" );

        GLCall(glTexImage2D(GL_TEXTURE_2D, 0, internalFormat, _width, _height, 0, dataFormat, GL_UNSIGNED_BYTE, _data));
    }

    void GLTexture2D::init_4_5() {
        GLCall(glCreateTextures(GL_TEXTURE_2D, 1, &_rendererID));

        GLenum internalFormat = 0;
        GLenum dataFormat = 0;
        if ( _bpp == 4) {
            internalFormat = GL_RGBA8;
            dataFormat = GL_RGBA;
        }
        else if ( _bpp == 3) {
            internalFormat = GL_RGB8;
            dataFormat = GL_RGB;
        }
        BACKEND_ASSERT( internalFormat&&dataFormat, "unsupported file type when loading texture!" );

        GLCall(glTextureStorage2D(_rendererID, 1, internalFormat, _width, _height));
        GLCall(glTextureSubImage2D(_rendererID, 0, 0, 0, _width, _height, dataFormat, GL_UNSIGNED_BYTE, _data));
    }
}
