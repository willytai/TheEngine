#ifndef __SHADER_H__
#define __SHADER_H__

#include "GLmacro.h"
#include <stdio.h>
#include <errno.h>
#include <string>
#include <string_view>
#include <unordered_map>
#include <glm/glm.hpp>

class Shader
{
public:
    Shader(const char* vertexShaderFile, const char* fragmentShaderFile);
    ~Shader();

    void bind() const;
    void unbind() const;

    void setUniform1i(const char* name, int value);
    void setUniform1f(const char* name, float value);
    void setUniform3f(const char* name, const glm::vec3& vec);
    void setUniform3f(const char* name, float f0, float f1, float f2);
    void setUniform4f(const char* name, const glm::vec4& vec);
    void setUniform4f(const char* name, float f0, float f1, float f2, float f3);
    void setUniformMat4f(const char* name, const glm::mat4& mat);

private:
    GLuint createShader(const char* vertexShaderFile, const char* fragmentShaderFile);
    GLuint compileShader(GLenum type, std::string& source, const char* filepath);
    GLint  getLocation(const char* name);

private:
    GLuint  _rendererID;

    // location cache
    std::unordered_map<std::string_view, GLint> _uniformLocationCache;
};

#endif /* __SHADER_H__ */
