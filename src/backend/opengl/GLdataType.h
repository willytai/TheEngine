#ifndef __GL_DATATYPE_H__
#define __GL_DATATYPE_H__

#include "backend/backend.h"
#include "core/renderer/buffer.h"
#include "glad/glad.h"

namespace Engine7414
{
    static GLenum toOpenGLDataType(const BufferDataType& dtype) {
        switch (dtype) {
            case BufferDataType::Float:  return GL_FLOAT;
            case BufferDataType::Int:    return GL_INT;
            case BufferDataType::uInt8:  return GL_UNSIGNED_BYTE;
            case BufferDataType::uInt32: return GL_UNSIGNED_INT;
            default: BACKEND_ASSERT( false, "Unsupported data type for OpenGL: {}", dtype ); return 0;
        }
    }
}

#endif /* __GL_DATATYPE_H__ */
