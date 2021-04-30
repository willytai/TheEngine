#ifndef __MTL_CONTEXT_H__
#define __MTL_CONTEXT_H__

#include "core/renderer/context.h"

#import <Metal/Metal.h>
#import <QuartzCore/QuartzCore.h>

struct GLFWwindow;

namespace Engine7414
{
    class MetalContext : public Context
    {
    public:
        MetalContext(GLFWwindow* handle);

        void init() override;
        void swapBuffers() override;
        void swapInterval(int interval) override;

        id<MTLDevice> device();

    private:
        GLFWwindow*   _handle;
        id<MTLDevice> _device;
    };
}

#endif /* __MTL_CONTEXT_H__ */
