#include "core/core.h"
#include "core/renderer/buffer.h"
#include "core/renderer/renderer.h"
#include "backend/OpenGL/GLbuffer.h"

namespace Engine7414
{
    VertexBuffer* VertexBuffer::create(const void* vertices, size_t size) {
        switch (Renderer::backend()) {
            case RendererBackend::OpenGL : return new GLVertexBuffer( vertices, size );
            default: CORE_ASSERT( false, "Unsupported Backend" );
        }
        return NULL;
    }

#define IndexBufferBaseClassImpl( ClassName, Type ) \
    ClassName* ClassName::create(const Type* indices, uint32_t count) { \
        switch (Renderer::backend()) { \
            case RendererBackend::OpenGL : return new GL##ClassName( indices, count ); \
            default: CORE_ASSERT( false, "Unsupported Backend" ); \
        } \
        return NULL; \
    }

    IndexBufferBaseClassImpl( IndexBufferUI8,  uint8_t )
    IndexBufferBaseClassImpl( IndexBufferUI32, uint32_t )
}
