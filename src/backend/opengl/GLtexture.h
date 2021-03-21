#ifndef __GL_TEXTURE_H__
#define __GL_TEXTURE_H__

#include "core/renderer/texture.h"
#include "backend/OpenGL/GLmacro.h"

namespace Engine7414
{
    class GLTexture2D : public Texture2D
    {
    public:
        GLTexture2D(const char* filepath);
        ~GLTexture2D();

        void bind(uint32_t slot = 0) const override;
        void unbind() const override;

        inline uint32_t width() const override { return _width; }
        inline uint32_t height() const override { return _height; }

    private:
        uint8_t*        _data;
        GLuint          _rendererID;
        uint32_t        _width;
        uint32_t        _height;
        uint32_t        _bpp; // bytes per pixel (EX: 4 channels in png)
    };
}
#endif /* __GL_TEXTURE_H__ */
