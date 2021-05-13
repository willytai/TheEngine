#include "backend/MTL/MTLtexture.h"
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
        CORE_ASSERT( false, "" );
    }

    MTLTexture2D::~MTLTexture2D() {
    }

    void MTLTexture2D::bind(uint32_t slot) const {
        CORE_ASSERT( false, "" );
    }

    void MTLTexture2D::unbind() const {
        CORE_ASSERT( false, "" );
    }

    void MTLTexture2D::setData(void* data, const uint32_t& size) {
        CORE_ASSERT( false, "" );
    }
}
