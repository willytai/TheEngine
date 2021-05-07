#ifndef __MTL_CONTEXT_H__
#define __MTL_CONTEXT_H__

#import <Metal/Metal.h>
#import <QuartzCore/QuartzCore.h>

#include "core/renderer/context.h"

struct GLFWwindow;

// this class stores all the non-transient objects for metal backend
@interface GlobalContext : NSObject
@property (nonatomic, strong) id<MTLDevice> nativeDevice;
@property (nonatomic, strong) id<MTLCommandQueue> commandQueue;
@property (nonatomic, strong) CAMetalLayer* swapChain;
@end

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
