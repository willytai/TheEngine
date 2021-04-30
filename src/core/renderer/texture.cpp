#include "core/renderer/texture.h"
#include "core/renderer/renderer.h"
#include "backend/OpenGL/GLtexture.h"
#include "backend/MTL/MTLtexture.h"

namespace Engine7414
{
    Ref<Texture2D> Texture2D::create(const uint32_t& width, const uint32_t& height) {
        switch (Renderer::backend()) {
            case RendererBackend::OpenGL: return CreateRef<GLTexture2D>( width, height );
            case RendererBackend::Metal: return CreateRef<MTLTexture2D>( width, height );
            default: CORE_ASSERT(false, "Unsupported Backend");
        }
        return NULL;
    }

    Ref<Texture2D> Texture2D::create(const uint32_t& width, const uint32_t& height, void* data) {
        switch (Renderer::backend()) {
            case RendererBackend::OpenGL: return CreateRef<GLTexture2D>( width, height, data );
            case RendererBackend::Metal: return CreateRef<MTLTexture2D>( width, height, data );
            default: CORE_ASSERT(false, "Unsupported Backend");
        }
        return NULL;
    }

    Ref<Texture2D> Texture2D::create(const char* filepath) {
        switch (Renderer::backend()) {
            case RendererBackend::OpenGL: return CreateRef<GLTexture2D>( filepath );
            case RendererBackend::Metal: return CreateRef<MTLTexture2D>( filepath );
            default: CORE_ASSERT(false, "Unsupported Backend");
        }
        return NULL;
    }
}
