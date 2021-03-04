#ifndef __VERTEX_BUFFER_LAYOUT_H__
#define __VERTEX_BUFFER_LAYOUT_H__

#include "util/log.h"
#include "GLmacro.h"
#include <vector>

struct VertexBufferElement
{
    GLenum      type;
    GLint       count;
    GLboolean   normalized;

    unsigned int typeSize() const {
        switch (type) {
            case GL_FLOAT:          return sizeof(GLfloat);
            case GL_UNSIGNED_INT:   return sizeof(GLuint);
            case GL_UNSIGNED_BYTE:  return sizeof(GLubyte);
            default: OPENGL_ERROR( "Unsupported element type for vertex buffer: {}", type ); assert(false);
        }
    }
};

class VertexBufferLayout
{
public:
    VertexBufferLayout() :
        _stride(0) {}
    ~VertexBufferLayout() {}

    template <typename T>
    void push(GLint count) {
        SYS_ERROR( "Got unsupported element type for vertex buffer\n\t\t{} {}:{}",
                    __PRETTY_FUNCTION__,
                    __FILE__,
                    __LINE__ );
        assert( false );
    }

    template <>
    void push<GLfloat>(GLint count) {
        _elements.push_back( { GL_FLOAT, count, GL_FALSE } );
        _stride += count * (int)sizeof( GLfloat );
    }

    template <>
    void push<GLuint>(GLint count) {
        _elements.push_back( { GL_UNSIGNED_INT, count, GL_FALSE } );
        _stride += count * (int)sizeof( GLuint );
    }

    template <>
    void push<GLubyte>(GLint count) {
        _elements.push_back( { GL_UNSIGNED_BYTE, count, GL_TRUE } );
        _stride += count * (int)sizeof( GLubyte );
    }

    inline const std::vector<VertexBufferElement>& elements() const { return _elements; }
    inline GLsizei stride() const { return _stride; }

private:
    std::vector<VertexBufferElement>    _elements;
    GLsizei                             _stride;
};

#endif /* __VERTEX_BUFFER_LAYOUT_H__ */
