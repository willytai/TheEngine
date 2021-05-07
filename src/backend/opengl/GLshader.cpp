#include "GLshader.h"
#include <filesystem>

namespace Engine7414
{

    GLShader::GLShader(const std::string& name, const char* shaderDir)
        : Shader(name)
    {
        std::string vShaderPath, fShaderPath;
        for (const auto& file : std::filesystem::directory_iterator( shaderDir ) ) {
            if ( file.is_directory() ) continue;
            auto path = file.path().string();
            if ( path.find("vertex") != std::string::npos  && file.path().extension() == ".glsl" ) {
                vShaderPath.swap( path );
            }
            else if ( path.find("fragment") != std::string::npos && file.path().extension() == ".glsl" ) {
                fShaderPath.swap( path );
            }
            else CORE_WARN( "got unrecognized file \'{}\' while loading shader", path );
        }
        _rendererID = this->createShader( vShaderPath.c_str(), fShaderPath.c_str() );
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
