#ifndef __APP_EVENTS_H__
#define __APP_EVENTS_H__

#include "core/event/baseEvent.h"

namespace Engine7414
{
    class WindowResizeEvent : public Event
    {
    public:
        WindowResizeEvent(uint32_t width, uint32_t height)
            : _width(width), _height(height) {}

        inline uint32_t width() const { return _width; }
        inline uint32_t height() const { return _height; }

        EVENT_CLASS( WindowResize )
    private:
        uint32_t _width;
        uint32_t _height;
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
