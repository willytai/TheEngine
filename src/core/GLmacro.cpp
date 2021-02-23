#include "GLmacro.h"

void GLClearError() {
    while ( glGetError() != GL_NO_ERROR );
}

bool GLLogCall(const char* function, const char* file, int line) {
    GLenum error = glGetError();
    if ( error ) {
        OPENGL_ERROR( "code {:02x}: {} {}:{}", error, function, file, line );
        return false;
    }
    return true;
}
