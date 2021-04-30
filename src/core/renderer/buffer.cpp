#include "core/core.h"
#include "core/renderer/buffer.h"
#include "core/renderer/renderer.h"
#include "backend/OpenGL/GLbuffer.h"
#include "backend/MTL/MTLbuffer.h"

namespace Engine7414
{
    Ref<VertexBuffer> VertexBuffer::create(size_t size) {
        switch (Renderer::backend()) {
            case RendererBackend::OpenGL: return CreateRef<GLVertexBuffer>(size);
            case RendererBackend::Metal: return CreateRef<MTLVertexBuffer>(size);
            default: CORE_ASSERT(false, "Unsupported Backend");
        }
        return NULL;
    }

    Ref<VertexBuffer> VertexBuffer::create(const void* vertices, size_t size) {
        switch (Renderer::backend()) {
            case RendererBackend::OpenGL : return CreateRef<GLVertexBuffer>( vertices, size );
            case RendererBackend::Metal : return CreateRef<MTLVertexBuffer>( vertices, size );
            default: CORE_ASSERT( false, "Unsupported Backend" );
        }
        return NULL;
    }

#define IndexBufferBaseClassImpl( ClassName, Type ) \
    Ref<ClassName> ClassName::create(const Type* indices, uint32_t count) { \
        switch (Renderer::backend()) { \
            case RendererBackend::OpenGL : return CreateRef<GL##ClassName>( indices, count ); \
            case RendererBackend::Metal : return CreateRef<MTL##ClassName>( indices, count ); \
            default: CORE_ASSERT( false, "Unsupported Backend" ); \
        } \
        return NULL; \
    }

    IndexBufferBaseClassImpl( IndexBufferUI8,  uint8_t )
    IndexBufferBaseClassImpl( IndexBufferUI32, uint32_t )
}
