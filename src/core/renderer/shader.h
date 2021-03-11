#ifndef __SHADER_H__
#define __SHADER_H__

namespace Engine7414
{
    class Shader
    {
    public:
        Shader(const char* vShaderPath, const char* fShaderPath)
                    : _vertex_shader_path(vShaderPath), _fragment_shader_path(fShaderPath) {}
        virtual ~Shader() {}

        virtual void bind() const = 0;
        virtual void unbind() const = 0;

        static Shader* create(const char* vShaderPath, const char* fShaderPath);

    protected:
        const char* _vertex_shader_path;
        const char* _fragment_shader_path;
    };
}

#endif /* __SHADER_H__ */
