#define GLFW_INCLUDE_NONE
#include <stdio.h>
#include <errno.h>
#include "renderer.h"
#include <GLFW/glfw3.h>

static GLuint CompileShader( GLenum type, std::string& source, const std::string& filename ) {
    FILE* file = fopen( filename.c_str(), "rb" );
    if ( !file ) {
        SYS_ERROR( "Error opening {}: {}", filename, strerror(errno) );
        return 0;
    }

    if ( fseek( file, 0, SEEK_END ) != 0 ) {
        SYS_ERROR( "Error reading {}: {}", filename, strerror(errno) );
        fclose( file );
        return 0;
    }

    long size;
    if ( (size = ftell( file )) == -1L ) {
        SYS_ERROR( "Error reading {}: {}", filename, strerror(errno) );
        fclose( file );
        return 0;
    }

    if ( fseek( file, 0, SEEK_SET ) != 0 ) {
        SYS_ERROR( "Error reading {}: {}", filename, strerror(errno) );
        fclose( file );
        return 0;
    }

    source.resize( (size_t)size );
    if ( fread( &source[0], sizeof(char), (size_t)size, file ) != (size_t)size ) {
        SYS_ERROR( "Error reading {}: {}", filename, strerror(errno) );
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

static GLuint createShader( const std::string& vertexShaderFile, const std::string& fragmentShaderFile ) {
    std::string vertexShader;
    std::string fragmentShader;

    GLCall( GLuint program = glCreateProgram() );
    GLuint vs = CompileShader( GL_VERTEX_SHADER, vertexShader, vertexShaderFile );
    GLuint fs = CompileShader( GL_FRAGMENT_SHADER, fragmentShader, fragmentShaderFile );

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

int main(int argc, char *argv[])
{
    util::Log::init( 4 );

    GLFWwindow* window = NULL;

    if ( glfwInit() ) {
        GLFW_INFO( "Successfully Initialized." );

        glfwWindowHint( GLFW_CONTEXT_VERSION_MAJOR, 3 );
        glfwWindowHint( GLFW_CONTEXT_VERSION_MINOR, 3 );
        glfwWindowHint( GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE );
        glfwWindowHint( GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE );
    }
    else {
        GLFW_ERROR( "Initialization Failed." );
        return -1;
    }

    if ( (window = glfwCreateWindow( 1280, 960, "test window", NULL, NULL )) != NULL ) {
        GLFW_INFO( "window created." );
    }
    else {
        GLFW_ERROR( "unable to create window." );
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent( window );
    glfwSwapInterval(1);

    if ( !gladLoadGLLoader((GLADloadproc)glfwGetProcAddress) ) {
        GLFW_ERROR( "Failed to initialize GLAD." );
        exit(EXIT_FAILURE);
    }

    float positions[] = {
        -0.5f, -0.5f,
         0.5f, -0.5f,
         0.5f,  0.5f,
        -0.5f,  0.5f
    };

    unsigned int indices[] = {
        0, 1, 2,
        0, 2, 3
    };

    // vertex buffer object
    VertexBuffer vb( positions, 8*sizeof(float) );

    // vertex array object
    GLuint vertexArrayID;
    GLCall( glGenVertexArrays( 1, &vertexArrayID ) );
    GLCall( glBindVertexArray( vertexArrayID ) );
    GLCall( glVertexAttribPointer( 0, 2, GL_FLOAT, GL_FALSE, 2*sizeof(float), 0 ) );
    GLCall( glEnableVertexAttribArray( 0 ) );

    // index buffer object
    IndexBufferUI ib( indices, 6 );

    GLuint shader;
    if ( (shader = createShader( "./resource/shader/vertex.glsl", "./resource/shader/fragment.glsl" )) == 0 ) {
        OPENGL_ERROR( "Failed to create shader!" );
        exit(EXIT_FAILURE);
    }
    GLCall( glUseProgram( shader ) );

    GLCall( GLint u_color_loc = glGetUniformLocation( shader, "u_color" ) );

    GLCall( glBindVertexArray(0) );
    GLCall( glUseProgram(0) );
    GLCall( glBindBuffer(GL_ARRAY_BUFFER, 0) );
    GLCall( glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0) );

    float r_channel = 1.0f;
    float intv = 0.05f;

    while ( !glfwWindowShouldClose(window) ) {
        GLCall( glClearColor( 0.2f, 0.3f, 0.3f, 1.0f ) );
        GLCall( glClear( GL_COLOR_BUFFER_BIT ) );

        GLCall( glUseProgram( shader ) );
        GLCall( glUniform4f( u_color_loc, r_channel, 0.3f, 0.8f, 1.0f ) );

        GLCall( glBindVertexArray( vertexArrayID ) );
        ib.bind();

        GLCall( glDrawElements( GL_TRIANGLES, ib.count(), GL_UNSIGNED_INT, nullptr ) );

        if ( r_channel > 1.0f ) intv = -0.05f;
        else if ( r_channel < 0.0f ) intv = 0.05f;
        r_channel += intv;

        glfwSwapBuffers( window );
        glfwPollEvents();
    }

    GLCall( glDeleteProgram( shader ) );
    glfwDestroyWindow( window );

    glfwTerminate();
    return 0;
}
