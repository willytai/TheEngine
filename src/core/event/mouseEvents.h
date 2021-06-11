#ifndef __MOUSE_EVENTS_H__
#define __MOUSE_EVENTS_H__

#include "core/event/baseEvent.h"
#include "core/input/codes.h"
#include <sstream>

namespace Engine7414
{
    class MouseMovedEvent : public Event
    {
    public:
        MouseMovedEvent(const float xpos, const float ypos)
            : _xpos(xpos), _ypos(ypos) {}

        // x coordinate
        inline float xPos() const { return _xpos; }
        // y coordinate
        inline float yPos() const { return _ypos; }

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

        // horizontal offset
        inline float xOffset() const { return _xoffset; }
        // virtical offset
        inline float yOffset() const { return _yoffset; }

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
    public:
        MouseButtonEvent(const MouseCode_t& button, const Mod_t& mods)
            : _button(button), _mods(mods) {}

        // mouse button
        inline virtual MouseCode_t button() const { return _button; }
        // modifier bits
        inline virtual Mod_t mods() const { return _mods; }

    protected:
        MouseCode_t _button; // the button (left/right/middle)
        Mod_t       _mods;   // modifier bits, indicate some other states
    };

    class MouseButtonPressedEvent : public MouseButtonEvent
    {
    public:
        MouseButtonPressedEvent(const MouseCode_t button, const Mod_t mods)
            : MouseButtonEvent( button, mods ) {}

        EVENT_CLASS( MouseButtonPressed );
    };

    class MouseButtonReleasedEvent : public MouseButtonEvent
    {
    public:
        MouseButtonReleasedEvent(const MouseCode_t button, const Mod_t mods)
            : MouseButtonEvent( button, mods ) {}

        EVENT_CLASS( MouseButtonReleased );
    };
}

#endif /* ifndef __MOUSE_EVENTS_H__ */
