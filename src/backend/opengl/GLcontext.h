#ifndef __GL_CONTEXT_H__
#define __GL_CONTEXT_H__
#define GLFW_INCLUDE_NONE

#include "core/renderer/context.h"
#include "GLFW/glfw3.h"

namespace Engine7414
{
    class OpenGLContext : public Context
    {
    public:
        OpenGLContext(GLFWwindow* handle);

        void init() override;
        void swapBuffers() override;

    private:
        GLFWwindow* _handle;
    };
}

#endif /* __GL_CONTEXT_H__ */
