#include "backend/MTL/MTLshader.h"
#include <filesystem>

namespace Engine7414
{

    MTLShader::MTLShader(const std::string& name, const char* shaderDir)
        : Shader(name)
    {
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
    }

    void MTLShader::unbind() const {
    }

}
