#ifndef __SHADER_H__
#define __SHADER_H__

#include "core/core.h"
#include "glm/glm.hpp"
#include <string>
#include <unordered_map>

namespace Engine7414
{
    class Shader
    {
    public:
        Shader(const std::string& name) : _name(name) {}
        virtual ~Shader() {}

        virtual void bind() const = 0;
        virtual void unbind() const = 0;
        virtual void setMat4f(const char* name, const glm::mat4& value) = 0;
        virtual void setInt1(const char* name, const int& value) = 0;

        static Ref<Shader> create(const std::string& name, const char* shaderPath);

    protected:
        std::string _name;
    };

    // a singleton, the renderer owns the shader dictionary
    class ShaderDict
    {
    public:
        Ref<Shader> load(const char* shaderPath);
        Ref<Shader> load(const std::string& name, const char* shaderPath);
        Ref<Shader> get(const std::string& name);        // this checks
        Ref<Shader> operator[](const std::string& name); // this doesn't check

        static ShaderDict& get() {
            static ShaderDict dict;
            return dict;
        }
    private:
        ShaderDict() = default;

        bool add(const std::string& name, const Ref<Shader>& shader);
        bool exists(const std::string& name);

    private:
        std::unordered_map<std::string, Ref<Shader> > _shaders;
    };
}

#endif /* __SHADER_H__ */
