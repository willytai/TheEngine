#ifndef __MTL_SHADER_HPP__
#define __MTL_SHADER_HPP__

#import "backend/MTL/MetalShader.h"

#include "core/renderer/shader.h"
#include <glm/glm.hpp>

namespace Engine7414
{
    class MTLShader : public Shader
    {
    public:
        MTLShader(const std::string& name, const char* shaderDir);
        ~MTLShader();

        void bind() const override;
        void unbind() const override;

        void setUniform1i(const char* name, int value);
        void setUniform1f(const char* name, float value);
        void setUniform3f(const char* name, const glm::vec3& vec);
        void setUniform3f(const char* name, float f0, float f1, float f2);
        void setVec4f(const char* name, const glm::vec4& value) override;
        void setMat4f(const char* name, const glm::mat4& value) override;
        void setInt1(const char* name, const int& value) override;
        void setIntArray(const char* name, const int* values, const int& count) override;

    private:
        // TODO
        // Metal shaders are library based, all the functions should be written in one single file
        // so making this a static class member is probably better
        MTLShaderHandle*    _handle;
    };

}
#endif /* __MTL_SHADER_HPP__ */
