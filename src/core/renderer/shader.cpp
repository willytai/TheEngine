#include "core/renderer/shader.h"
#include "core/renderer/renderer.h"
#include "backend/OpenGL/GLshader.h"
#include "backend/MTL/MTLshader.h"

namespace Engine7414
{
    Ref<Shader> Shader::create(const std::string& name, const char* shaderPath) {
        switch (Renderer::backend()) {
            case RendererBackend::OpenGL: return CreateRef<GLShader>( name, shaderPath );
            case RendererBackend::Metal: return CreateRef<MTLShader>( name, shaderPath );
            default: CORE_ASSERT( false, "Unsupported Backend" );
        }
        return NULL;
    }

    Ref<Shader> ShaderDict::load(const char* shaderPath) {
        // set name
        // a shader in ./resource/shader/texture will be named as 'texture'
        std::string_view sview( shaderPath );
        if ( sview.back() == '/' || sview.back() == '\\' ) sview.remove_suffix(1);
        auto pos = sview.find_last_of("/\\");
        pos = pos == std::string::npos ? 0 : pos+1;
        return this->load( std::string( sview.substr(pos) ), shaderPath );
    }

    Ref<Shader> ShaderDict::load(const std::string& name, const char* shaderPath) {
        auto shader = Shader::create( name, shaderPath );
        if ( !this->add( name, shader ) ) CORE_ERROR( "shader \'{}\' failed to load", name );
        return shader;
    }

    Ref<Shader> ShaderDict::get(const std::string& name) {
#ifdef ENGINE_DEBUG
        CORE_ASSERT( this->exists(name), "shader \'{}\' doesn't exist", name );
#endif
        return (*this)[name];
    }

    Ref<Shader> ShaderDict::operator[](const std::string& name) {
        return _shaders[name];
    }

    bool ShaderDict::add(const std::string& name, const Ref<Shader>& shader) {
        auto [_, check] = _shaders.emplace( name, shader );
        if ( !check) CORE_ERROR( "shader \'{}\' already exists", name );
        return check;
    }

    bool ShaderDict::exists(const std::string& name) {
        return _shaders.find( name ) != _shaders.end();
    }
}
