#ifndef __MTL_CONTEXT_H__
#define __MTL_CONTEXT_H__
#define GLFW_INCLUDE_NONE
#define GLFW_EXPOSE_NATIVE_COCOA

#include "core/renderer/context.h"
#include <GLFW/glfw3.h>
#include <GLFW/glfw3native.h>

namespace Engine7414
{
    class MetalContext : public Context
    {
    public:
        MetalContext(GLFWwindow* handle);

        void init() override;
        void swapBuffers() override;
        void swapInterval(int interval) override;

        void* device() override;

    private:
        GLFWwindow*   _handle;
        id<MTLDevice> _device;
    };
}

#endif /* __MTL_CONTEXT_H__ */
