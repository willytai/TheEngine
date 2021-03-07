#ifndef __APP_EVENTS_H__
#define __APP_EVENTS_H__

#include "core/event/baseEvent.h"

namespace Engine7414
{
    class WindowResizeEvent : public Event
    {
    public:
        WindowResizeEvent(int width, int height)
            : _width(width), _height(height) {}

        inline int width() const { return _width; }
        inline int height() const { return _height; }

        EVENT_CLASS( WindowResize )
    private:
        int _width;
        int _height;
    };

    class WindowCloseEvent : public Event
    {
    public:
        EVENT_CLASS( WindowClose )
    };

    class WindowIconifyEvent : public Event
    {
    public:
        EVENT_CLASS( WindowIconify )
    };
}

#endif /* __APP_EVENTS_H__ */
