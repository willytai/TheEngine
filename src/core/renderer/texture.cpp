#include "core/renderer/texture.h"
#include "core/renderer/renderer.h"

#ifdef __APPLE__
#import "backend/MTL/MTLtexture.h"
#else
#include "backend/OpenGL/GLtexture.h"
#endif

namespace Engine7414
{
    Ref<Texture2D> Texture2D::create(const uint32_t& width, const uint32_t& height) {
        switch (Renderer::backend()) {
            case RendererBackend::OpenGL:
            {
            #ifdef __APPLE__
                CORE_WARN( "OpenGL not supported on OS X, forcing Metal backend" );
                [[clang::fallthrough]];
            #else
                return CreateRef<GLTexture2D>( width, height );
            #endif
            }
            case RendererBackend::Metal: return CreateRef<MTLTexture2D>( width, height );
            default: CORE_ASSERT(false, "Unsupported Backend");
        }
        return NULL;
    }

    Ref<Texture2D> Texture2D::create(const uint32_t& width, const uint32_t& height, void* data) {
        switch (Renderer::backend()) {
            case RendererBackend::OpenGL:
            {
            #ifdef __APPLE__
                CORE_WARN( "OpenGL not supported on OS X, forcing Metal backend" );
                [[clang::fallthrough]];
            #else
                return CreateRef<GLTexture2D>( width, height, data );
            #endif
            }
            case RendererBackend::Metal: return CreateRef<MTLTexture2D>( width, height, data );
            default: CORE_ASSERT(false, "Unsupported Backend");
        }
        return NULL;
    }

    Ref<Texture2D> Texture2D::create(const char* filepath) {
        switch (Renderer::backend()) {
            case RendererBackend::OpenGL:
            {
            #ifdef __APPLE__
                CORE_WARN( "OpenGL not supported on OS X, forcing Metal backend" );
                [[clang::fallthrough]];
            #else
                return CreateRef<GLTexture2D>( filepath );
            #endif
            }
            case RendererBackend::Metal: return CreateRef<MTLTexture2D>( filepath );
            default: CORE_ASSERT(false, "Unsupported Backend");
        }
        return NULL;
    }
}
