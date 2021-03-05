#ifndef __WINDOW_H__
#define __WINDOW_H__

#include "core/event/event.h"
#include <functional>
#include <string>

namespace Engine7414
{
    /* An interface class */
    class Window
    {
    public:
        typedef std::function<void(Event&)> eventCallbackFn;

    public:
        Window(const char* title) : _title(title) {}
        virtual ~Window() {}

        /* access functions */
        virtual int getWidth() const = 0;
        virtual int getHeight() const = 0;
        virtual bool VSync() const = 0;
        virtual const char* title() const { return _title.c_str(); }

        /* setting functions */
        virtual void setEventCallback(const eventCallbackFn& fn) = 0;
        virtual void enableVSync() = 0;
        virtual void disbaleVSync() = 0;

        /* other */
        virtual void onUpdate() = 0;

        /* Implemented per platfrom */
        static Window* create(const char* title, int width, int height, bool vsync=true);

    private:
        std::string _title;
    };
}

#endif /* __WINDOW_H__ */
