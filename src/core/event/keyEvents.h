#ifndef __KEY_EVENTS_H__
#define __KEY_EVENTS_H__

#include "core/event/baseEvent.h"
#include "core/input/codes.h"
#include <sstream>

namespace Engine7414
{
    class KeyEvent : public Event
    {
    protected:
        KeyEvent(const KeyCode_t& code, const Mod_t& mods)
            : _code(code), _mods(mods) {}

        // key code
        inline KeyCode_t key() const { return _code; }
        // modifier bits
        inline Mod_t mods() const { return _mods; }

        KeyCode_t _code;
        Mod_t     _mods;
    };

    class KeyPressedEvent : public KeyEvent
    {
    public:
        KeyPressedEvent(KeyCode_t code, Mod_t mods, bool repeat)
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
        KeyReleasedEvent(KeyCode_t code, Mod_t mods)
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
