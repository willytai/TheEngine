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
        GLTexture2D(const uint32_t& width, const uint32_t& height);
        GLTexture2D(const uint32_t& width, const uint32_t& height, void* data);
        ~GLTexture2D();

        void bind(uint32_t slot = 0) const override;
        void unbind() const override;
        void setData(void* data, const uint32_t& size) override;

        inline int width() const override { return _width; }
        inline int height() const override { return _height; }

    private:
        void init_4_1(); // for opengl 4.1 and above (OS X only supports up to OpenGL 4.1)
        void init_4_5(); // for opengl 4.5 and above

    private:
        uint8_t*        _data;
        GLuint          _rendererID;
        int             _width;
        int             _height;
        int             _bpp; // bytes per pixel (EX: 4 channels in png)
    };
}
#endif /* __GL_TEXTURE_H__ */
