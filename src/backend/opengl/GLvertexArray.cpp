#include "backend/OpenGL/GLvertexArray.h"
#include "backend/OpenGL/GLdataType.h"

namespace Engine7414
{
    GLVertexArray::GLVertexArray() 
        : _attrIndex(0)
    {
        GLCall( glGenVertexArrays( 1, &_rendererID ) );
    }

    GLVertexArray::~GLVertexArray() {
        GLCall( glDeleteVertexArrays( 1, &_rendererID ) );
    }

    void GLVertexArray::addVertexBuffer(const Ref<VertexBuffer>& vertexBuffer) {
        BACKEND_ASSERT( vertexBuffer->layout().elements().size(), "vertex buffer has no layout!" );
        GLCall( glBindVertexArray( _rendererID ) );
        vertexBuffer->bind();

        const auto& layout = vertexBuffer->layout();
        for (const auto& element : layout.elements()) {
            switch (element.dtype) {
                case BufferDataType::Float:
                {
                    GLCall( glVertexAttribPointer( _attrIndex, (GLint)element.count, toOpenGLDataType(element.dtype),
                                                   element.normalized?GL_TRUE:GL_FALSE, (GLsizei)layout.stride(),
                                                   (const void*)(intptr_t)element.offset ) );
                    GLCall( glEnableVertexAttribArray( _attrIndex++ ) );
                    break;
                }
                case BufferDataType::uInt32:
                case BufferDataType::uInt8:
                case BufferDataType::Int:
                {
                    GLCall( glVertexAttribIPointer(_attrIndex, (GLint)element.count, toOpenGLDataType(element.dtype),
                                                   (GLsizei)layout.stride(),
                                                   (const void*)(intptr_t)element.offset));
                    GLCall( glEnableVertexAttribArray(_attrIndex++));
                    break;
                }
                default: CORE_ERROR("unsupported shader data type"); break;
            }
        }

        this->_vertexBuffers.push_back( vertexBuffer );
    }

    void GLVertexArray::setIndexBuffer(const Ref<IndexBuffer>& indexBuffer) {
        GLCall( glBindVertexArray( _rendererID ) );
        indexBuffer->bind();
        _indexBuffer = indexBuffer;
    }

    void GLVertexArray::bind() const {
        GLCall( glBindVertexArray( _rendererID ) );
    }

    void GLVertexArray::unbind() const {
        GLCall( glBindVertexArray( 0 ) );
    }

}
