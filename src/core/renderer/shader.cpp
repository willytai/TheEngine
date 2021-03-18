#include "core/renderer/shader.h"
#include "core/renderer/renderer.h"
#include "backend/OpenGL/GLshader.h"

namespace Engine7414
{
    Ref<Shader> Shader::create(const char* vShaderPath, const char* fShaderPath) {
        switch (Renderer::backend()) {
            case RendererBackend::OpenGL: return CreateRef<GLShader>( vShaderPath, fShaderPath );
            default: CORE_ASSERT( false, "Unsupported Backend" );
        }
        return NULL;
    }
}
