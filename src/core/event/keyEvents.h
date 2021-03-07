#ifndef __KEY_EVENTS_H__
#define __KEY_EVENTS_H__

#include "core/event/baseEvent.h"
#include <sstream>

namespace Engine7414
{
    class KeyEvent : public Event
    {
    protected:
        typedef int KeyCode;
        typedef int KeyMods;
    protected:
        KeyEvent(const KeyCode& code, const KeyMods& mods)
            : _code(code), _mods(mods) {}

        // key code
        inline KeyCode keycode() const { return _code; }
        // modifier bits
        inline KeyMods keymods() const { return _mods; }

        KeyCode _code;
        KeyMods _mods;
    };

    class KeyPressedEvent : public KeyEvent
    {
    public:
        KeyPressedEvent(KeyCode code, KeyMods mods, bool repeat)
            : KeyEvent( code, mods ), _repeat(repeat) {}

        // a repeat key press event or not
        inline bool repeat() const { return _repeat; }

        std::string toString() const override {
            std::stringstream ss;
            ss << this->name() << (_repeat?" repeat":" single") << " code: " << _code;
            return ss.str();
        }

        EVENT_CLASS( KeyPressed )
    private:
        bool _repeat;
    };

    class KeyReleasedEvent : public KeyEvent
    {
    public:
        KeyReleasedEvent(KeyCode code, KeyMods mods)
            : KeyEvent( code, mods ) {}

        std::string toString() const override {
            std::stringstream ss;
            ss << this->name() << " code: " << _code;
            return ss.str();
        }

        EVENT_CLASS( KeyReleased )
    };
}

#endif /* __KEY_EVENTS_H__ */
