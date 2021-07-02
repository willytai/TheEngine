#ifndef __SHADER_H__
#define __SHADER_H__

#include "core/core.h"
#include "glm/glm.hpp"
#include <string>
#include <unordered_map>

namespace Engine7414
{
    // forward declaration
    class UniformBuffer;

    struct UniformHandle
    {
        // TODO remove these in release version
        UniformBuffer* buffer = nullptr;    // just for validation, not really going to use it
        const char*    name = "";           // name of the uniform

        uint32_t       bindingIndex = 0; // the binding point, also use this as the buffer index
        size_t         offset = 0;       // the offset in the uniform buffer
        size_t         size = 0;         // size of the uniform, in bytes
        const void*    data = nullptr;   // the actual data
    };

    class Shader
    {
    public:
        Shader(const std::string& name) : _name(name) {}
        virtual ~Shader() {}

        virtual void bind() const = 0;
        virtual void unbind() const = 0;
        virtual void setMat4f(const char* name, const glm::mat4& value) = 0;
        virtual void setVec4f(const char* name, const glm::vec4& value) = 0;
        virtual void setInt1(const char* name, const int& value) = 0;
        virtual void setIntArray(const char* name, const int* value, const int& count) = 0;

        static Ref<Shader> create(const std::string& name, const char* shaderPath);

    protected:
        std::string _name;
    };

    // a singleton, the renderer owns the shader library
    class ShaderLibrary
    {
    public:
        Ref<Shader> load(const char* shaderPath);
        Ref<Shader> load(const std::string& name, const char* shaderPath);
        Ref<Shader> get(const std::string& name);        // this checks
        Ref<Shader> operator[](const std::string& name); // this doesn't check

        static ShaderLibrary& get() {
            static ShaderLibrary dict;
            return dict;
        }

        static void uploadGlobalUniforms(const std::vector<UniformHandle>& uniformHandles) {
            get().uploadUniforms(uniformHandles);
        }
        static void registerGlobalUniform(UniformHandle& handle) {
            get().registerUniform(handle);
        }
        static void submitGlobalUniforms() {
            get().submitUniforms();
        }
    private:
        ShaderLibrary() = default;

        bool add(const std::string& name, const Ref<Shader>& shader);
        bool exists(const std::string& name);

        void uploadUniforms(const std::vector<UniformHandle>& uniformHandles);
        void registerUniform(UniformHandle& handle);
        void submitUniforms();

    private:
        std::unordered_map<std::string, Ref<Shader> > _shaders;

    protected:
        std::vector<Ref<UniformBuffer> > _globalUniformBuffer;
    };
}

#endif /* __SHADER_H__ */
