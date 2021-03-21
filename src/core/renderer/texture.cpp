#include "core/renderer/texture.h"
#include "core/renderer/renderer.h"
#include "backend/OpenGL/GLtexture.h"

namespace Engine7414
{
    Ref<Texture2D> Engine7414::Texture2D::create(const char* filepath) {
        switch (Renderer::backend()) {
            case RendererBackend::OpenGL: CreateRef<GLTexture2D>( filepath );
            default: CORE_ASSERT(false, "Unsupported Backend");
        }
        return NULL;
    }

}