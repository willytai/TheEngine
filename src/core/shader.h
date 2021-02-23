#ifndef __SHADER_H__
#define __SHADER_H__

#include "GLmacro.h"
#include <stdio.h>
#include <errno.h>
#include <string>
#include <string_view>
#include <unordered_map>

class Shader
{
public:
    Shader(const char* vertexShaderFile, const char* fragmentShaderFile);
    ~Shader();

    void bind() const;
    void unbind() const;

    void setUniform4f(const char* name, float f0, float f1, float f2, float f3);

private:
    GLuint createShader(const char* vertexShaderFile, const char* fragmentShaderFile);
    GLuint compileShader(GLenum type, std::string& source, const char* filepath);

private:
    GLuint  _rendererID;

    // location cache
    std::unordered_map<std::string_view, GLint> _uniformLocationCache;
};

#endif /* __SHADER_H__ */
