#include "shader.h"

Shader::Shader(const char* vertexShaderFile, const char* fragmentShaderFile) {
    _rendererID = this->createShader( vertexShaderFile, fragmentShaderFile );
}

GLuint Shader::createShader(const char* vertexShaderFile, const char* fragmentShaderFile) {
    std::string vertexShader;
    std::string fragmentShader;

    GLCall( GLuint program = glCreateProgram() );
    GLuint vs = this->compileShader( GL_VERTEX_SHADER, vertexShader, vertexShaderFile );
    GLuint fs = this->compileShader( GL_FRAGMENT_SHADER, fragmentShader, fragmentShaderFile );

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

Shader::~Shader() {
    GLCall( glDeleteProgram( _rendererID ) );
}

GLuint Shader::compileShader(GLenum type, std::string& source, const char* filepath) {
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
        OPENGL_ERROR( "{}", msg );

        GLCall( glDeleteShader( id ) );
    }

    return id;
}

GLint Shader::getLocation(const char* name) {
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

void Shader::setUniform4f(const char* name, const glm::vec4& vec) {
    this->setUniform4f( name, vec[0], vec[1], vec[2], vec[3] );
}

void Shader::setUniform4f(const char* name, float f0, float f1, float f2, float f3) {
    GLCall( glUniform4f( this->getLocation(name), f0, f1, f2, f3 ) );
}

void Shader::setUniform3f(const char* name, const glm::vec3& vec) {
    this->setUniform3f( name, vec[0], vec[1], vec[2] );
}

void Shader::setUniform3f(const char* name, float f0, float f1, float f2) {
    GLCall( glUniform3f( this->getLocation(name), f0, f1, f2 ) );
}

void Shader::setUniform1i(const char* name, int value) {
    GLCall( glUniform1i( this->getLocation(name), value ) );
}

void Shader::setUniformMat4f(const char* name, const glm::mat4& mat) {
    GLCall( glUniformMatrix4fv( this->getLocation(name), 1, GL_FALSE, &mat[0][0] ) );
}

void Shader::bind() const {
    GLCall( glUseProgram( _rendererID ) );
}

void Shader::unbind() const {
    GLCall( glUseProgram( 0 ) );
}
