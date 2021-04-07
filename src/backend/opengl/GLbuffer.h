#ifndef __GL_BUFFER_H__
#define __GL_BUFFER_H__

#include "backend/OpenGL/GLmacro.h"
#include "core/renderer/buffer.h"

namespace Engine7414
{

    class GLVertexBuffer : public VertexBuffer
    {
    public:
        GLVertexBuffer(size_t size);
        GLVertexBuffer(const void* vertices, size_t size);
        ~GLVertexBuffer();

        void bind() const override;
        void unbind() const override;

        void setData(const void* data, const size_t& size) override;

    private:
        GLuint  _rendererID;
    };

#define GLIndexBufferClass( baseName, type) \
    class GL##baseName : public baseName \
    { \
    public: \
        GL##baseName(const type* data, uint32_t count); \
        ~GL##baseName(); \
 \
        void bind() const override; \
        void unbind() const override; \
 \
    private: \
        GLuint  _rendererID; \
    }

    GLIndexBufferClass( IndexBufferUI8,  uint8_t );
    GLIndexBufferClass( IndexBufferUI32, uint32_t );
}
#endif /* __GL_BUFFER_H__ */
