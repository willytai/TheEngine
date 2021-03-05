#ifndef __EVENT_H__
#define __EVENT_H__

#include <iostream>
#include <string>

namespace Engine7414
{
    enum class EventType
    {
        None = 0,
        WindowClose, WindowResize, 
        KeyPressed, KeyReleased,
        MouseButtonPressed, MouseButtonReleased, MouseMoved, MouseScrolled
    };

#define EVENT_CLASS(etype) \
        static EventType staticType() { return EventType::etype; } \
        inline EventType type() const override { return staticType(); } \
        inline const char* name() const override { return #etype; }

    class Event
    {
        friend class EventDispatcher;
    public:
        virtual EventType type() const = 0;
        virtual const char* name() const = 0;
        virtual std::string toString() const { return this->name(); }

    protected:
        bool _handled;
    };

    class EventDispatcher
    {
        template <typename T>
        using eventFn = std::function<bool(T&)>;
    public:
        EventDispatcher(Event& e) : _event(e) {}

        template <typename T>
        bool dispatch(eventFn<T> fn) {
            if ( _event.type() == T::staticType() ) {
                _event._handled = fn(*(T*)&_event);
                return true;
            }
            return false;
        }

    private:
        Event& _event;
    };

    inline std::ostream& operator<<(std::ostream& os, const Event& e) {
        return os << e.toString();
    }
}

#endif /* __EVENT_H__ */
