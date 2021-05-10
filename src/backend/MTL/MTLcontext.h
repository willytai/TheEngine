#ifndef __MTL_CONTEXT_H__
#define __MTL_CONTEXT_H__

#import "backend/MTL/MetalContext.h"

#include "core/renderer/context.h"

struct GLFWwindow;

namespace Engine7414
{
    class MTLContext : public Context
    {
        static MTLContext* __instance__;
    public:
        MTLContext(GLFWwindow* handle);

        void init() override;
        void swapBuffers() override;
        void swapInterval(int interval) override;

        static GlobalContext* getContext();
    private:
        GLFWwindow*     _handle;
        GlobalContext*  _context;
    };
}

#endif /* __MTL_CONTEXT_H__ */
