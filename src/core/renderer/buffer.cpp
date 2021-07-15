#include "core/core.h"
#include "core/renderer/buffer.h"
#include "core/renderer/renderer.h"

#ifdef __APPLE__
#import "backend/MTL/MTLbuffer.h"
#else
#include "backend/OpenGL/GLbuffer.h"
#endif

namespace Engine7414
{
    std::ostream& operator << (std::ostream& os, const BufferDataType& dtype) {
        switch (dtype) {
            case BufferDataType::Float:  os << "Float"; break;
            case BufferDataType::Int:    os << "Int";   break;
            case BufferDataType::uInt8:  os << "uInt8"; break;
            case BufferDataType::uInt16: os << "uInt16"; break;
            case BufferDataType::uInt32: os << "uInt32"; break;
            default: os << "Undefined"; break;
        }
        return os;
    }

    Ref<VertexBuffer> VertexBuffer::create(size_t size) {
        switch (Renderer::backend()) {
            case RendererBackend::OpenGL:
            {
            #ifdef __APPLE__
                CORE_WARN( "OpenGL not supported on OS X, forcing Metal backend" );
                [[clang::fallthrough]];
            #else
                return CreateRef<GLVertexBuffer>(size);
            #endif
            }
            case RendererBackend::Metal: return CreateRef<MTLVertexBuffer>(size);
            default: CORE_ASSERT(false, "Unsupported Backend");
        }
        return NULL;
    }

    Ref<VertexBuffer> VertexBuffer::create(size_t size, uint32_t index) {
        switch (Renderer::backend()) {
            case RendererBackend::OpenGL:
            {
            #ifdef __APPLE__
                CORE_WARN( "OpenGL not supported on OS X, forcing Metal backend" );
                [[clang::fallthrough]];
            #else
                return CreateRef<GLVertexBuffer>(size);
            #endif
            }
            case RendererBackend::Metal: return CreateRef<MTLVertexBuffer>(size, index);
            default: CORE_ASSERT(false, "Unsupported Backend");
        }
        return NULL;
    }

    Ref<VertexBuffer> VertexBuffer::create(const void* vertices, size_t size) {
        switch (Renderer::backend()) {
            case RendererBackend::OpenGL:
            {
            #ifdef __APPLE__
                CORE_WARN( "OpenGL not supported on OS X, forcing Metal backend" );
                [[clang::fallthrough]];
            #else
                return CreateRef<GLVertexBuffer>( vertices, size );
            #endif
            }
            case RendererBackend::Metal: return CreateRef<MTLVertexBuffer>( vertices, size );
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

#define IndexBufferBaseClassImplApple( ClassName, Type ) \
    Ref<ClassName> ClassName::create(const Type* indices, uint32_t count) { \
        if (Renderer::backend() != RendererBackend::Metal) { \
            CORE_WARN( "OpenGL not supported on OS X, forcing Metal backend" ); \
        } \
        return CreateRef<MTL##ClassName>( indices, count ); \
    }

#ifdef __APPLE__
    IndexBufferBaseClassImplApple( IndexBufferUI8,  uint8_t )
    IndexBufferBaseClassImplApple( IndexBufferUI32, uint32_t )
#else
    IndexBufferBaseClassImpl( IndexBufferUI8,  uint8_t )
    IndexBufferBaseClassImpl( IndexBufferUI32, uint32_t )
#endif
}
