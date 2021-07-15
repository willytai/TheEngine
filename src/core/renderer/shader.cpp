#include "core/renderer/shader.h"
#include "core/renderer/renderer.h"
#include "backend/OpenGL/GLshader.h"

namespace Engine7414
{
    Ref<Shader> Shader::create(const std::string& name, const char* shaderPath) {
        switch (Renderer::backend()) {
            case RendererBackend::OpenGL: return CreateRef<GLShader>( name, shaderPath );
            default: CORE_ASSERT( false, "Unsupported Backend" );
        }
        return NULL;
    }

    Ref<Shader> ShaderLibrary::load(const char* shaderPath) {
        // set name
        // a shader in ./resource/shader/texture will be named as 'texture'
        std::string_view sview( shaderPath );
        if ( sview.back() == '/' || sview.back() == '\\' ) sview.remove_suffix(1);
        auto pos = sview.find_last_of("/\\");
        pos = pos == std::string::npos ? 0 : pos+1;
        return this->load( std::string( sview.substr(pos) ), shaderPath );
    }

    Ref<Shader> ShaderLibrary::load(const std::string& name, const char* shaderPath) {
        auto shader = Shader::create( name, shaderPath );
        if ( !this->add( name, shader ) ) CORE_ERROR( "shader \'{}\' failed to load" );
        return shader;
    }

    Ref<Shader> ShaderLibrary::get(const std::string& name) {
#ifdef ENGINE_DEBUG
        CORE_ASSERT( this->exists(name), "shader \'{}\' doesn't exist" );
#endif
        return (*this)[name];
    }

    Ref<Shader> ShaderLibrary::operator[](const std::string& name) {
        return _shaders[name];
    }

    bool ShaderLibrary::add(const std::string& name, const Ref<Shader>& shader) {
        auto [_, check] = _shaders.emplace( name, shader );
        if ( !check) CORE_ERROR( "shader \'{}\' already exists" );
        return check;
    }

    bool ShaderLibrary::exists(const std::string& name) {
        return _shaders.find( name ) != _shaders.end();
    }

    void ShaderLibrary::uploadUniforms(const std::vector<UniformHandle>& uniformHandles) {
        for (const auto& handle : uniformHandles) {
            CORE_ASSERT(handle.buffer == _globalUniformBuffer[handle.bindingIndex].get(), "");
            _globalUniformBuffer[handle.bindingIndex]->bind();
            _globalUniformBuffer[handle.bindingIndex]->setData(handle.offset, handle.size, handle.data);
        }
    }

    void ShaderLibrary::registerUniform(UniformHandle& handle) {
        if (_globalUniformBuffer.size() < handle.bindingIndex + 1) {
            _globalUniformBuffer.resize(handle.bindingIndex + 1);
        }
        if (!_globalUniformBuffer[handle.bindingIndex]) {
            _globalUniformBuffer[handle.bindingIndex] = UniformBuffer::create();
        }

        // register a space in the dedicated uniform buffer for this uniform
        // CORE_ASSERT(_globalUniformBuffer[handle.bindingIndex]->size() == handle.offset, "{} != {}", _globalUniformBuffer[handle.bindingIndex]->size(), handle.offset);
        _globalUniformBuffer[handle.bindingIndex]->registerUniformSize(handle.offset, handle.size);
        handle.buffer = _globalUniformBuffer[handle.bindingIndex].get();
    }

    void ShaderLibrary::submitUniforms() {
        for (uint32_t index = 0; index < _globalUniformBuffer.size(); ++index) {
            auto& buffer = _globalUniformBuffer[index];
            if (buffer) buffer->init(index);
        }
    }
}
