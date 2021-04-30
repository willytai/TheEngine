#ifndef __MTL_TEXTURE_H__
#define __MTL_TEXTURE_H__

#include "core/renderer/texture.h"

namespace Engine7414
{
    class MTLTexture2D : public Texture2D
    {
    public:
        MTLTexture2D(const char* filepath);
        MTLTexture2D(const uint32_t& width, const uint32_t& height);
        MTLTexture2D(const uint32_t& width, const uint32_t& height, void* data);
        ~MTLTexture2D();

        void bind(uint32_t slot = 0) const override;
        void unbind() const override;
        void setData(void* data, const uint32_t& size) override;

        inline int width() const override { return _width; }
        inline int height() const override { return _height; }

    private:
        uint8_t*        _data;
        int             _width;
        int             _height;
        int             _bpp; // bytes per pixel (EX: 4 channels in png)
    };
}
#endif /* __MTL_TEXTURE_H__ */
