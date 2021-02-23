#include "vertexArray.h"

VertexArray::VertexArray() {
    GLCall( glGenVertexArrays( 1, &_rendererID ) );
}

VertexArray::~VertexArray() {
    GLCall( glDeleteVertexArrays( 1, &_rendererID ) );
}

void VertexArray::addLayout(const VertexBuffer& vb, const VertexBufferLayout& layout) {
    (*this).bind();
    vb.bind();
    const auto& elements = layout.elements();
    unsigned int offset = 0;
    for (unsigned int i = 0; i < elements.size(); ++i) {
        const auto& element = elements[i];
        GLCall( glVertexAttribPointer( i, element.count, element.type, element.normalized,
                                       layout.stride(), (const GLvoid*)offset ) );
        GLCall( glEnableVertexAttribArray( i ) );
        offset += (unsigned int)element.count * element.typeSize();
    }
}

void VertexArray::bind() const {
    GLCall( glBindVertexArray( _rendererID ) );
}

void VertexArray::unbind() const {
    GLCall( glBindVertexArray( 0 ) );
}
