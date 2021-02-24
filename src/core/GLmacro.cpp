#include "GLmacro.h"

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wconversion"
#pragma GCC diagnostic ignored "-Wsign-compare"
#define STB_IMAGE_IMPLEMENTATION
#include <stb/stb_image.h>
#pragma GCC diagnostic pop

const char* GLErrorStr(GLenum error) {
    switch (error) {
        case GL_INVALID_ENUM: return "GL_INVALID_ENUM";
        case GL_INVALID_VALUE: return "GL_INVALID_VALUE";
        case GL_INVALID_OPERATION: return "GL_INVALID_OPERATION";
        case GL_INVALID_FRAMEBUFFER_OPERATION: return "GL_INVALID_FRAMEBUFFER_OPERATION";
        case GL_OUT_OF_MEMORY: return "GL_OUT_OF_MEMORY";
        default: return "Undefined Error";
    }
}

void GLClearError() {
    while ( glGetError() != GL_NO_ERROR );
}

bool GLLogCall(const char* function, const char* file, int line) {
    GLenum error = glGetError();
    if ( error ) {
        OPENGL_ERROR( "{} ({:02x}): {} {}:{}", GLErrorStr(error), error, function, file, line );
        return false;
    }
    return true;
}
