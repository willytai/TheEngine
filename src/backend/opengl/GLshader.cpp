#include "backend/opengl/GLshader.h"
#include "core/util/timer.h"

#include <filesystem>
#include <shaderc/shaderc.hpp>
#include <spirv-cross/spirv_glsl.hpp>
#include <spirv-cross/spirv_msl.hpp>

namespace Engine7414
{
    const char* GLShader::cacheDirectory() {
        static const char* path = "assets/cache/shader/opengl";
        if (!std::filesystem::exists(path)) {
            std::filesystem::create_directories(path);
        }
        return path;
    }

    const char* GLShader::cachedFileExtension(GLenum type) {
        switch (type) {
            case GL_VERTEX_SHADER: return ".vert.cache";
            case GL_FRAGMENT_SHADER: return ".frag.cache";
        }
        CORE_ASSERT(false, "");
        return "";
    }

    void GLShader::readRawText(const char* filepath, std::string& result) {
        FILE* file = fopen(filepath, "rb");
        if (!file) {
            SYS_ERROR("Error opening {}: {}", filepath, strerror(errno));
            return;
        }

        if (fseek(file, 0, SEEK_END) != 0) {
            SYS_ERROR("Error reading {}: {}", filepath, strerror(errno));
            fclose(file);
            return;
        }

        long size;
        if ((size = ftell(file)) == -1L) {
            SYS_ERROR("Error reading {}: {}", filepath, strerror(errno));
            fclose(file);
            return;
        }

        if (fseek(file, 0, SEEK_SET) != 0) {
            SYS_ERROR("Error reading {}: {}", filepath, strerror(errno));
            fclose(file);
            return;
        }

        result.clear();
        result.resize((size_t)size);
        if (fread(result.data(), sizeof(char), (size_t)size, file) != (size_t)size) {
            SYS_ERROR("Error reading {}: {}", filepath, strerror(errno));
            fclose(file);
            return;
        }
        fclose(file);
    }

    void GLShader::compilationStat(GLuint shader, GLenum type) {
        GLint compiled;
        GLCall(glGetShaderiv(shader, GL_COMPILE_STATUS, &compiled));
        if (compiled != GL_TRUE) {
            GLint logLength;
            GLCall(glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &logLength));

            std::string msg; msg.resize(logLength);
            GLCall(glGetShaderInfoLog(shader, logLength, &logLength, msg.data()));

            OPENGL_ERROR("Failed to compile {} shader!", (type == GL_VERTEX_SHADER ? "vertex" : "fragment"));
            if (msg.back() == '\n') msg.back() = '\0';
            OPENGL_ERROR("{}", msg);
            CORE_ASSERT(false, "");
        }
    }

    GLShader::GLShader(const std::string& name, const char* shaderDir)
        : Shader(name)
    {
        std::string vShaderPath, fShaderPath;
        for (const auto& file : std::filesystem::directory_iterator( shaderDir ) ) {
            if ( file.is_directory() ) continue;
            auto path = file.path().string();
            if ( path.find("vertex") != std::string::npos ) {
                vShaderPath.swap( path );
            }
            else if ( path.find("fragment") != std::string::npos ) {
                fShaderPath.swap( path );
            }
            else CORE_WARN( "got unrecognized file \'{}\' while loading shader", path );
        }
        // _rendererID = this->createShader( vShaderPath.c_str(), fShaderPath.c_str() );

        {
            Timer t;
        
            this->compileOrGetSPRIV(GL_VERTEX_SHADER, vShaderPath.c_str());
            this->compileOrGetSPRIV(GL_FRAGMENT_SHADER, fShaderPath.c_str());
            this->createShaderProgram();
        
            OPENGL_DEBUG("shader compilation: {} ms", t.elapsed_ms());
        }

    }

    GLuint GLShader::createShader(const char* vShaderPath, const char* fShaderPath) {
        std::string vertexShader;
        std::string fragmentShader;

        GLCall( GLuint program = glCreateProgram() );
        GLuint vs = this->compileShader( GL_VERTEX_SHADER, vertexShader, vShaderPath );
        GLuint fs = this->compileShader( GL_FRAGMENT_SHADER, fragmentShader, fShaderPath );

        GLCall( glAttachShader( program, vs ) );
        GLCall( glAttachShader( program, fs ) );
        GLCall( glLinkProgram( program ) );
        GLCall( glValidateProgram( program ) );

        GLint result;
        GLCall( glGetProgramiv( program, GL_LINK_STATUS, &result ) );
        if ( result == GL_FALSE ) {
            GLint length;
            GLCall( glGetProgramiv( program, GL_INFO_LOG_LENGTH, &length ) );
            char* msg = (char*)alloca( (unsigned)length*sizeof(char) );
            GLCall( glGetProgramInfoLog( program, length, &length, msg ) );
            OPENGL_ERROR( "Failed to link shader" );
            OPENGL_ERROR( "{}", msg );
        }

        GLCall( glDeleteShader( vs ) );
        GLCall( glDeleteShader( fs ) );

        return program;
    }

    GLShader::~GLShader() {
        GLCall( glDeleteProgram( _rendererID ) );
    }

    GLuint GLShader::compileShader(GLenum type, std::string& source, const char* filepath) {
        FILE* file = fopen( filepath, "rb" );
        if ( !file ) {
            SYS_ERROR( "Error opening {}: {}", filepath, strerror(errno) );
            return 0;
        }

        if ( fseek( file, 0, SEEK_END ) != 0 ) {
            SYS_ERROR( "Error reading {}: {}", filepath, strerror(errno) );
            fclose( file );
            return 0;
        }

        long size;
        if ( (size = ftell( file )) == -1L ) {
            SYS_ERROR( "Error reading {}: {}", filepath, strerror(errno) );
            fclose( file );
            return 0;
        }

        if ( fseek( file, 0, SEEK_SET ) != 0 ) {
            SYS_ERROR( "Error reading {}: {}", filepath, strerror(errno) );
            fclose( file );
            return 0;
        }

        source.resize( (size_t)size );
        if ( fread( &source[0], sizeof(char), (size_t)size, file ) != (size_t)size ) {
            SYS_ERROR( "Error reading {}: {}", filepath, strerror(errno) );
            fclose( file );
            return 0;
        }
        fclose( file );

        GLCall( GLuint id = glCreateShader( type ) );
        const char* c_src = source.c_str();
        GLCall( glShaderSource( id, 1, &c_src, NULL ) );
        GLCall( glCompileShader( id ) );

        GLint result;
        GLCall( glGetShaderiv( id, GL_COMPILE_STATUS, &result ) );
        if ( result == GL_FALSE ) {
            GLint length;
            GLCall( glGetShaderiv( id, GL_INFO_LOG_LENGTH, &length ) );
            char* msg = (char*)alloca( (unsigned)length*sizeof(char) );
            GLCall( glGetShaderInfoLog( id, length, &length, msg ) );
            OPENGL_ERROR( "Failed to compile {} shader!", (type==GL_VERTEX_SHADER?"vertex":"fragment") );
            if ( msg[length-1] == '\n' ) msg[length-1] = '\0';
            OPENGL_ERROR( "{}", msg );

            GLCall( glDeleteShader( id ) );
        }

        return id;
    }

    void GLShader::compileOrGetSPRIV(GLenum type, const char* filepath) {
        // compiler configuration
        shaderc::Compiler compiler;
        shaderc::CompileOptions options;
        options.SetOptimizationLevel(shaderc_optimization_level_performance);
        options.SetTargetEnvironment(shaderc_target_env_opengl, shaderc_env_version_opengl_4_5);

        // cache path
        std::filesystem::path cacheDirectory = GLShader::cacheDirectory();
        std::filesystem::path cachePath = cacheDirectory / (_name + GLShader::cachedFileExtension(type));

        // the target shader and the shaderc type
        std::vector<uint32_t>* spirvDataPtr = type == GL_VERTEX_SHADER ? &_vertexSPIRV : &_fragmentSPIRV;
        auto shadercGlslShaderType = type == GL_VERTEX_SHADER ? shaderc_glsl_vertex_shader : shaderc_glsl_fragment_shader;

        // read from cache or udpate
        FILE* file = _wfopen(cachePath.c_str(), L"rb");
        if (file) {
            fseek(file, 0, SEEK_END);
            auto size = ftell(file);
            spirvDataPtr->resize(size/sizeof(uint32_t));
            fseek(file, 0, SEEK_SET);
            fread((char*)spirvDataPtr->data(), sizeof(char), size, file);
            fclose(file);
        }
        else {
            std::string shaderSource;
            GLShader::readRawText(filepath, shaderSource);
            shaderc::SpvCompilationResult spvResult = compiler.CompileGlslToSpv(shaderSource, shadercGlslShaderType, filepath, options);
            if (spvResult.GetCompilationStatus() != shaderc_compilation_status_success) {
                OPENGL_ERROR(spvResult.GetErrorMessage());
                CORE_ASSERT(false, "");
            }
            *spirvDataPtr = std::vector<uint32_t>(spvResult.cbegin(), spvResult.cend());
            file = _wfopen(cachePath.c_str(), L"wb");
            if (file) {
                fwrite(spirvDataPtr->data(), sizeof(uint32_t), spirvDataPtr->size(), file);
                fclose(file);
            }
            else OPENGL_WARN("unable to open {} for caching", cachePath.generic_string());
        }

        this->reflect(type, *spirvDataPtr);
    }

    void GLShader::reflect(GLenum type, const std::vector<uint32_t>& spirvBinary) {
        spirv_cross::CompilerGLSL glsl(spirvBinary);
        spirv_cross::ShaderResources resources = glsl.get_shader_resources();

        OPENGL_DEBUG("Reflect - [{}: {}]", type == GL_VERTEX_SHADER ? "VERTEX" : "FRAGMENT", _name);
        OPENGL_DEBUG("     {} uniform buffer(s)", resources.uniform_buffers.size());
        OPENGL_DEBUG("     {} resource(s)", resources.sampled_images.size());
        OPENGL_DEBUG("     Uniform Buffer(s):");
        for (const auto& ubuffer : resources.uniform_buffers) {
            const auto& bufferType = glsl.get_type(ubuffer.base_type_id);
            auto bufferSize = glsl.get_declared_struct_size(bufferType);
            auto binding = glsl.get_decoration(ubuffer.id, spv::DecorationBinding);
            auto members = bufferType.member_types.size();
            OPENGL_DEBUG("         {}", ubuffer.name);
            OPENGL_DEBUG("           size = {}", bufferSize);
            OPENGL_DEBUG("           binding = {}", binding);
            OPENGL_DEBUG("           members = {}", members);
        }

        // spirv_cross::CompilerMSL msl(spirvBinary);
        // spirv_cross::CompilerMSL::Options options;
        // options.set_msl_version(2, 1);
        // msl.set_msl_options(options);
        // static int i = 0;
        // static std::string name = "shader.msl";
        // name += char(i+'0');
        // FILE* metalOut = fopen(name.c_str(), "w");
        // auto data = msl.compile();
        // fwrite(data.c_str(), sizeof(char), data.size(), metalOut);
        // fclose(metalOut);
    }

    void GLShader::createShaderProgram() {
        GLuint program = GLCall( glCreateProgram() );
        GLuint vs = GLCall(glCreateShader(GL_VERTEX_SHADER));
        GLuint fs = GLCall(glCreateShader(GL_FRAGMENT_SHADER));

        // vertex shader
        GLCall(glShaderBinary(1, &vs, GL_SHADER_BINARY_FORMAT_SPIR_V, _vertexSPIRV.data(), (GLsizei)(_vertexSPIRV.size() * sizeof(uint32_t))));
        GLCall(glSpecializeShader(vs, "main", 0, nullptr, nullptr));
        GLShader::compilationStat(vs, GL_VERTEX_SHADER);

        // fragment shader
        GLCall(glShaderBinary(1, &fs, GL_SHADER_BINARY_FORMAT_SPIR_V, _fragmentSPIRV.data(), (GLsizei)(_fragmentSPIRV.size() * sizeof(uint32_t))));
        GLCall(glSpecializeShader(fs, "main", 0, nullptr, nullptr));
        GLShader::compilationStat(fs, GL_FRAGMENT_SHADER);

        // attach, link, validate
        GLCall(glAttachShader(program, vs));
        GLCall(glAttachShader(program, fs));
        GLCall(glLinkProgram(program));

        // link check
        GLint linked;
        GLCall(glGetProgramiv(program, GL_LINK_STATUS, &linked));
        if (linked != GL_TRUE) {
            GLint logLength;
            GLCall(glGetProgramiv(program, GL_INFO_LOG_LENGTH, &logLength));
            std::string msg; msg.reserve(logLength);
            GLCall(glGetProgramInfoLog(program, logLength, &logLength, msg.data()));
            OPENGL_ERROR("Failed to link shader: {}", msg);
        }

        // free
        GLCall(glDeleteShader(vs));
        GLCall(glDeleteShader(fs));

        _rendererID = program;
    }

    GLint GLShader::getLocation(const char* name) {
        GLint location;
        std::unordered_map<std::string_view, GLint>::iterator it;
        if ( (it = _uniformLocationCache.find( name )) != _uniformLocationCache.end() ) {
            return it->second;
        }
        else {
            GLCall( location = glGetUniformLocation( _rendererID, name ) );
            _uniformLocationCache[name] = location;
        }
        if ( location == -1 ) OPENGL_WARN( "uniform \'{}\' doesn't exist!", name );
        return location;
    }

    void GLShader::setVec4f(const char* name, const glm::vec4& value) {
        GLCall( glUniform4f( this->getLocation(name), value.r, value.g, value.b, value.a ) );
    }

    void GLShader::setUniform3f(const char* name, const glm::vec3& vec) {
        this->setUniform3f( name, vec[0], vec[1], vec[2] );
    }

    void GLShader::setUniform3f(const char* name, float f0, float f1, float f2) {
        GLCall( glUniform3f( this->getLocation(name), f0, f1, f2 ) );
    }

    void GLShader::setUniform1f(const char *name, float value) {
        GLCall( glUniform1f( this->getLocation(name), value ) );
    }

    void GLShader::setUniform1i(const char* name, int value) {
        GLCall( glUniform1i( this->getLocation(name), value ) );
    }

    void GLShader::setMat4f(const char* name, const glm::mat4& value) {
        GLCall( glUniformMatrix4fv( this->getLocation(name), 1, GL_FALSE, &value[0][0] ) );
    }

    void GLShader::setInt1(const char* name, const int& value) {
        GLCall( glUniform1i( this->getLocation(name), value ) );
    }

    void GLShader::setIntArray(const char* name, const int* values, const int& count) {
        GLCall( glUniform1iv( this->getLocation(name), count, values) );
    }

    void GLShader::bind() const {
        GLCall( glUseProgram( _rendererID ) );
    }

    void GLShader::unbind() const {
        GLCall( glUseProgram( 0 ) );
    }

}
