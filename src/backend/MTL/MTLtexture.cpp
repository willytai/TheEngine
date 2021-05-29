#include "backend/MTL/MTLtexture.h"
#include "backend/backend.h"
#include <stb/stb_image.h>

namespace Engine7414
{
    MTLTexture2D::MTLTexture2D(const uint32_t& width, const uint32_t& height) :
        _data(NULL),
        _width((int)width), _height((int)height), _bpp(4)
    {
        CORE_ASSERT( false, "" );
    }

    MTLTexture2D::MTLTexture2D(const uint32_t& width, const uint32_t& height, void* data) :
        _data(NULL),
        _width((int)width), _height((int)height), _bpp(4)
    {
        _handle = [[MTLTextureHandle alloc] initWithData:data Width:width Height:height Bpp:_bpp];
    }

    MTLTexture2D::MTLTexture2D(const char* filepath) :
        _data(NULL),
        _width(0), _height(0), _bpp(0)
    {
        // load image
        stbi_set_flip_vertically_on_load(1);
        _data = stbi_load( filepath, &_width, &_height, &_bpp, 0 );
        BACKEND_VERIFY( _data, "stb_image: Failed to load {}", filepath );
        _handle = [[MTLTextureHandle alloc] initWithData:(void*)_data Width:(uint32_t)_width Height:(uint32_t)_height Bpp:_bpp];
        if (_data) stbi_image_free(_data);
        _data = NULL;
        // CORE_ASSERT( false, "" );
    }

    MTLTexture2D::~MTLTexture2D() {
    }

    void MTLTexture2D::bind(uint32_t slot) const {
        [_handle bindToSlot:slot];
    }

    void MTLTexture2D::unbind() const {
        CORE_ASSERT( false, "" );
    }

    void MTLTexture2D::setData(void* data, const uint32_t& size) {
        CORE_ASSERT( false, "" );
    }
}
