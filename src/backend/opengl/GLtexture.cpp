#include "backend/OpenGL/GLtexture.h"
#include <stb/stb_image.h>

namespace Engine7414
{
    GLTexture2D::GLTexture2D(const char* filepath)
        : _rendererID(0), _data(NULL),
        _width(0), _height(0), _bpp(0)
    {
        // load image
        stbi_set_flip_vertically_on_load(1);
        int width, height, bpp;
        _data = stbi_load( filepath, &width, &height, &bpp, 0 );
        BACKEND_VERIFY( _data, "stb_image: Failed to load {}", filepath );
        _width = width;
        _height = height;
        _bpp = bpp;

        GLCall(glGenTextures(1, &_rendererID));
        GLCall(glBindTexture(GL_TEXTURE_2D, _rendererID));

        // linear filtering for magnifying/minifying operations
        GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
        GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));

        // clamp to boarder
        GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER));
        GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER));

        GLCall(glTextureSubImage2D(GL_TEXTURE_2D, 0, 0, 0, _width, _height, GL_RGB, GL_UNSIGNED_BYTE, _data));

        if (_data) stbi_image_free(_data);
    }

    GLTexture2D::~GLTexture2D() {
        GLCall(glDeleteTextures(1, &_rendererID));
    }

    void GLTexture2D::bind(uint32_t slot) const {
        GLCall(glBindTextureUnit(GL_TEXTURE0 + slot, _rendererID));
    }

    void GLTexture2D::unbind() const {
        GLCall(glBindTexture(GL_TEXTURE_2D, 0));
    }
}