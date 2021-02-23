#include "indexBuffer.h"

IndexBufferUI::IndexBufferUI(const GLuint* data, unsigned int count) {
    GLCall( glGenBuffers( 1, &_rendererID ) );
    GLCall( glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, _rendererID ) );
    GLCall( glBufferData( GL_ELEMENT_ARRAY_BUFFER, count*sizeof(GLuint), data, GL_STATIC_DRAW ) );
    _count = count;
}

IndexBufferUI::~IndexBufferUI() {
    GLCall( glDeleteBuffers( 1, &_rendererID ) );
}

void IndexBufferUI::bind() const {
    GLCall( glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, _rendererID ) );
}

void IndexBufferUI::unbind() const {
    GLCall( glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, 0 ) );
}
