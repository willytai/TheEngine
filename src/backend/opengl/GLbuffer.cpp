#include "GLbuffer.h"

namespace Engine7414
{

    GLVertexBuffer::GLVertexBuffer(size_t size) {
        GLCall( glGenBuffers( 1, &_rendererID ) );
        GLCall( glBindBuffer( GL_ARRAY_BUFFER, _rendererID ) );
        GLCall( glBufferData( GL_ARRAY_BUFFER, (GLsizeiptr)size, NULL, GL_DYNAMIC_DRAW ) );
    }

    GLVertexBuffer::GLVertexBuffer(const void* vertices, size_t size) {
        GLCall(glGenBuffers(1, &_rendererID));
        GLCall(glBindBuffer(GL_ARRAY_BUFFER, _rendererID));
        GLCall(glBufferData(GL_ARRAY_BUFFER, (GLsizeiptr)size, vertices, GL_STATIC_DRAW));
    }

    GLVertexBuffer::~GLVertexBuffer() {
        GLCall( glDeleteBuffers( 1, &_rendererID ) );
    }

    void GLVertexBuffer::bind() const {
        GLCall( glBindBuffer( GL_ARRAY_BUFFER, _rendererID ) );
    }

    void GLVertexBuffer::unbind() const {
        GLCall( glBindBuffer( GL_ARRAY_BUFFER, 0 ) );
    }

    void* GLVertexBuffer::getCPUStorage() const {
        // OpenGL doesn't allocate storage on system memory for sychronization
        // with the GPU. Manual allocation is required.
        return NULL;
    }

    void GLVertexBuffer::setData(const void* data, const size_t& size) {
        GLCall(glBindBuffer(GL_ARRAY_BUFFER, _rendererID));
        GLCall(glBufferSubData(GL_ARRAY_BUFFER, 0, size, data));
    }

#define GLIndexBufferClassImpl( baseName, type) \
    GL##baseName::GL##baseName(const type* data, uint32_t count) { \
        GLCall( glGenBuffers( 1, &_rendererID ) ); \
        GLCall( glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, _rendererID ) ); \
        GLCall( glBufferData( GL_ELEMENT_ARRAY_BUFFER, count*sizeof(type), data, GL_STATIC_DRAW ) ); \
        _count = count; \
    } \
 \
    GL##baseName::~GL##baseName() { \
        GLCall( glDeleteBuffers( 1, &_rendererID ) ); \
    } \
 \
    void GL##baseName::bind() const { \
        GLCall( glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, _rendererID ) ); \
    } \
 \
    void GL##baseName::unbind() const { \
        GLCall( glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, 0 ) ); \
    }

    GLIndexBufferClassImpl( IndexBufferUI8,  uint8_t )
    GLIndexBufferClassImpl( IndexBufferUI32, uint32_t )
}
