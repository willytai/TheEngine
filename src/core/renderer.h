#ifndef __RENDERER_H__
#define __RENDERER_H__

#include "GLmacro.h"
#include "vertexBuffer.h"
#include "indexBuffer.h"
#include "vertexBufferLayout.h"
#include "vertexArray.h"
#include "shader.h"
#include "texture.h"
#include "camera.h"

class Renderer
{
public:
    Renderer();
    ~Renderer();

    void clear() const;
    void drawElement(const VertexArray& va, const IndexBufferUI& ib, const Shader& shader) const;
    void drawArray(const VertexArray& va, const Shader& shader, int count) const;

private:
};

#endif /* __RENDERER_H__ */
