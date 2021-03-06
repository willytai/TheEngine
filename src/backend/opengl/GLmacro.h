#ifndef __GL_MACRO_H__
#define __GL_MACRO_H__

#include <glad/glad.h>
#include "backend/backend.h"
#include "core/util/log.h"

#ifdef ENGINE_DEBUG
    #define GL_ASSERT(x) \
        if ( !(x) ) exit(EXIT_FAILURE)

    // the modern OpenGL debug output isn't guarenteed to work on OS X
    // using the tranditional way instead
    #ifdef __APPLE__
        #define GLCall(x) \
            GLClearError(); \
            x; \
            GL_ASSERT(GLLogCall(#x, __FILE__, __LINE__))
        void GLClearError();
        bool GLLogCall(const char* function, const char* file, int line);
    #else
        #define GLCall(x) x
    #endif

#else
    #define GL_ASSERT(x)
    #define GLCall(x) x
#endif

#endif /* __GL_MACRO_H__ */
