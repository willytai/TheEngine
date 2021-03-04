#ifndef __GL_MACRO_H__
#define __GL_MACRO_H__

#include "util/log.h"
#include <glad/glad.h>

#define GL_ASSERT(x) \
    if ( !(x) ) exit(EXIT_FAILURE)

#define GLCall(x) \
    GLClearError(); \
    x; \
    GL_ASSERT(GLLogCall(#x, __FILE__, __LINE__))

void GLClearError();
bool GLLogCall(const char* function, const char* file, int line);

#endif /* __GL_MACRO_H__ */
