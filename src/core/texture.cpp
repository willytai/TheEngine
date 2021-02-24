#include "texture.h"
#include <stb/stb_image.h>

Texture::Texture(const char* filepath)
    : _rendererID(0), _localbuffer(NULL),
      _width(0), _height(0), _bpp(0) {

    stbi_set_flip_vertically_on_load(1);
    _localbuffer = stbi_load( filepath, &_width, &_height, &_bpp, 4 );

    GLCall( glGenTextures( 1, &_rendererID ) );
    GLCall( glBindTexture( GL_TEXTURE_2D, _rendererID ) );

    // linear filtering for magnifying/minifying operations
    GLCall( glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR ) );
    GLCall( glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR ) );

    // clamp to boarder
    GLCall( glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER ) );
    GLCall( glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER ) );

    GLCall( glTexImage2D( GL_TEXTURE_2D, 0, GL_RGBA8, _width, _height, 0, GL_RGBA, GL_UNSIGNED_BYTE, _localbuffer ) );
    GLCall( glBindTexture( GL_TEXTURE_2D, 0 ) );

    if ( _localbuffer ) stbi_image_free( _localbuffer );
}

Texture::~Texture() {
    GLCall( glDeleteTextures( 1, &_rendererID ) );
}

void Texture::bind(unsigned int slot) const {
    GLCall( glActiveTexture( GL_TEXTURE0 + slot ) );
    GLCall( glBindTexture( GL_TEXTURE_2D, _rendererID ) );
}

void Texture::unbind() const {
    GLCall( glBindTexture( GL_TEXTURE_2D, 0 ) );
}
