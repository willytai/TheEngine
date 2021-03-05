#ifndef __MOUSE_EVENTS_H__
#define __MOUSE_EVENTS_H__

#include "core/event/event.h"
#include <sstream>

namespace Engine7414
{
    class MouseMovedEvent : public Event
    {
    public:
        MouseMovedEvent(const float xpos, const float ypos)
            : _xpos(xpos), _ypos(ypos) {}

        std::string toString() const override {
            std::stringstream ss;
            ss << this->name() << ": " << _xpos << ' ' << _ypos;
            return ss.str();
        }

        EVENT_CLASS( MouseMoved )
    private:
        float   _xpos;
        float   _ypos;
    };

    class MouseScrolledEvent : public Event
    {
    public:
        MouseScrolledEvent(const float xoffset, const float yoffset)
            : _xoffset(xoffset), _yoffset(yoffset) {}

        std::string toString() const override {
            std::stringstream ss;
            ss << this->name() << ": " << _xoffset << ' ' << _yoffset;
            return ss.str();
        }

        EVENT_CLASS( MouseScrolled )
    private:
        float   _xoffset; // horizontal scroll
        float   _yoffset; // virtical scroll
    };

    class MouseButtonEvent : public Event
    {
    protected:
        typedef int MouseCode;
        typedef int MouseMods;
    protected:
        MouseButtonEvent(const MouseCode& button, const MouseMods& mods)
            : _button(button), _mods(mods) {}

        MouseCode _button; // the button (left/right)
        MouseMods _mods;   // modifier bits, indicate some other states
    };

    class MouseButtonPressedEvent : public MouseButtonEvent
    {
    public:
        MouseButtonPressedEvent(const MouseCode button, const MouseMods mods)
            : MouseButtonEvent( button, mods ) {}

        EVENT_CLASS( MouseButtonPressed );
    };

    class MouseButtonReleasedEvent : public MouseButtonEvent
    {
    public:
        MouseButtonReleasedEvent(const MouseCode button, const MouseMods mods)
            : MouseButtonEvent( button, mods ) {}

        EVENT_CLASS( MouseButtonReleased );
    };
}

#endif /* ifndef __MOUSE_EVENTS_H__ */
