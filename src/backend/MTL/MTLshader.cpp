#include "backend/MTL/MTLshader.h"
#include <filesystem>

#import "backend/MTL/MTLrenderAPI.h"

namespace Engine7414
{

    MTLShader::MTLShader(const std::string& name, const char* shaderDir) :
        Shader(name),
        _handle(nil)
    {
        std::string shaderPath;
        for (const auto& file : std::filesystem::directory_iterator( shaderDir ) ) {
            if ( file.is_directory() ) continue;
            auto path = file.path().string();
            if ( file.path().extension() == ".metal" ) {
                shaderPath.swap( path );
            }
            else CORE_WARN( "got unrecognized file \'{}\' while loading shader", path );
        }

        _handle = [[MTLShaderHandle alloc] initWithCSourcePath:shaderPath.c_str()];
    }

    MTLShader::~MTLShader() {
    }

    void MTLShader::setVec4f(const char* name, const glm::vec4& value) {
    }

    void MTLShader::setUniform3f(const char* name, const glm::vec3& vec) {
    }

    void MTLShader::setUniform3f(const char* name, float f0, float f1, float f2) {
    }

    void MTLShader::setUniform1f(const char *name, float value) {
    }

    void MTLShader::setUniform1i(const char* name, int value) {
    }

    void MTLShader::setMat4f(const char* name, const glm::mat4& value) {
    }

    void MTLShader::setInt1(const char* name, const int& value) {
    }

    void MTLShader::setIntArray(const char* name, const int* values, const int& count) {
    }

    void MTLShader::bind() const {
        auto* vFunc = [_handle getFunctionWithName:@"vertexMain"];
        auto* fFunc = [_handle getFunctionWithName:@"fragmentMain"];
        auto* renderHandle = MTLRenderAPI::getRenderHandle();
        renderHandle.rpsCacheKey.vertexFunc = vFunc;
        renderHandle.rpsCacheKey.fragmentFunc = fFunc;
    }

    void MTLShader::unbind() const {
    }

}
