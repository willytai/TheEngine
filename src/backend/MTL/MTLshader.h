#ifndef __MTL_SHADER_H__
#define __MTL_SHADER_H__

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

        // uniform upload in metal is typeless (just memcpy)
        // making sure the uniform that's uploaded has the same type would be the user's responsibility
        void setVec4f(const char* name, const glm::vec4& value) override;
        void setMat4f(const char* name, const glm::mat4& value) override;
        void setInt1(const char* name, const int& value) override;
        void setIntArray(const char* name, const int* values, const int& count) override;

    private:
        void genUniformPosMap();
        size_t getUniformPos(const char* name) const;

    private:
        MTLShaderHandle*    _handle;

        // the offset of the uniform in the uniform buffer
        std::unordered_map<std::string, size_t>     _uniformPosMap;
    };

}
#endif /* __MTL_SHADER_H__ */
