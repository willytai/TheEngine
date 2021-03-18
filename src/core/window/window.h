#ifndef __WINDOW_H__
#define __WINDOW_H__

#include "core/core.h"
#include "core/event/event.h"
#include "core/renderer/context.h"
#include "backend/backend.h"
#include <functional>
#include <string>

namespace Engine7414
{
    struct WindowProps
    {
        const char*     title;
        int             width;
        int             height;
        RendererBackend rendererBackend;
        bool            vsync = true;
    };

    /* An interface class */
    class Window
    {
    public:
        typedef std::function<void(Event&)> eventCallbackFn;

    public:
        Window(const char* title) : _title(title) {}
        virtual ~Window() = default;

        /* access functions */
        virtual int getWidth() const = 0;
        virtual int getHeight() const = 0;
        virtual bool VSync() const = 0;
        virtual void* nativeWindow() = 0;
        virtual const char* title() const { return _title.c_str(); }

        /* setting functions */
        virtual void setEventCallback(const eventCallbackFn& fn) = 0;
        virtual void enableVSync() = 0;
        virtual void disbaleVSync() = 0;

        /* other */
        virtual void onUpdate() = 0;

        /* Implemented per platfrom */
        /* Will automatically bind the created window with the input handler class */
        static Scoped<Window> create(const WindowProps& props);

    protected:
        std::string     _title;
        Scoped<Context> _context;
    };
}

#endif /* __WINDOW_H__ */
