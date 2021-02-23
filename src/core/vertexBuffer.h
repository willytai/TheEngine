#ifndef __VERTEX_BUFFER_H__
#define __VERTEX_BUFFER_H__

#include "GLmacro.h"

class VertexBuffer
{
public:
    VertexBuffer(const void* data, unsigned int size);
    ~VertexBuffer();

    void bind() const;
    void unbind() const;
private:
    GLuint  _rendererID;
};

#endif /* __VERTEX_BUFFER_H__ */
