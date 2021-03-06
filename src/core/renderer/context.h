#ifndef __CONTEXT_H__
#define __CONTEXT_H__

namespace Engine7414
{
    class Context
    {
    public:
        Context() {}
        virtual ~Context() = default;

        virtual void init() = 0;
        virtual void swapBuffers() = 0;
        virtual void swapInterval(int interval) = 0;
        virtual void* device() { return 0; }
    };
}

#endif /* ifndef __CONTEXT_H__ */
