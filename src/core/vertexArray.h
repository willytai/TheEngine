#ifndef __VERTEX_ARRAY_H__
#define __VERTEX_ARRAY_H__

#include "GLmacro.h"
#include "vertexBuffer.h"
#include "vertexBufferLayout.h"
#include <vector>

class VertexArray
{
public:
    VertexArray();
    ~VertexArray();

    void bind() const;
    void unbind() const;

    void addLayout(const VertexBuffer& vb, const VertexBufferLayout& layout);

private:
    GLuint  _rendererID;
};

#endif /* __VERTEX_ARRAY_H__ */
