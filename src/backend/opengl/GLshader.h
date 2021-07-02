#ifndef __GL_SHADER_H__
#define __GL_SHADER_H__

#include "backend/OpenGL/GLmacro.h"
#include "core/renderer/shader.h"
#include <stdio.h>
#include <errno.h>
#include <string>
#include <string_view>
#include <unordered_map>
#include <glm/glm.hpp>

namespace Engine7414
{

    class GLShader : public Shader
    {
    public:
        GLShader(const std::string& name, const char* shaderDir);
        ~GLShader();

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
        GLuint createShader(const char* vertexShaderFile, const char* fragmentShaderFile);
        GLuint compileShader(GLenum type, std::string& source, const char* filepath);
        GLint  getLocation(const char* name);

        void compileOrGetSPRIV(GLenum type, const char* filepath);
        void reflect(GLenum type, const std::vector<uint32_t>& spirvBinary);
        void createShaderProgram();

    private:
        static const char* cacheDirectory();
        static const char* cachedFileExtension(GLenum type);
        static void readRawText(const char* filepath, std::string& result);
        static void compilationStat(GLuint shader, GLenum type);

    private:
        GLuint  _rendererID;

        // spirv binary
        std::vector<uint32_t> _vertexSPIRV;
        std::vector<uint32_t> _fragmentSPIRV;

        // location cache
        std::unordered_map<std::string_view, GLint> _uniformLocationCache;
    };

}
#endif /* __GL_SHADER_H__ */
