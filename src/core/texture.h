#ifndef __TEXTURE_H__
#define __TEXTURE_H__

#include "GLmacro.h"

class Texture
{
public:
    Texture(const char* filepath);
    ~Texture();

    void bind(unsigned int slot = 0) const;
    void unbind() const;

private:
    GLuint          _rendererID;
    unsigned char*  _localbuffer;
    int             _width;
    int             _height;
    int             _bpp; // bytes per pixel (4 channels in png)
};

#endif /* __TEXTURE_H__ */
