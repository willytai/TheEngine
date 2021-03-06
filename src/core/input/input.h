#ifndef __INPUT_H__
#define __INPUT_H__

#include "core/core.h"
#include "core/window/window.h"
#include "core/input/codes.h"

#include <glm/glm.hpp>

namespace Engine7414
{
    class Input
    {
    public:
        static bool keyPressed(KeyCode_t key) { return __instance__->keyPressedImpl(key); }
        static bool mouseButtonPressed(MouseCode_t button) { return __instance__->mouseButtonPressedImpl(button); }
        static glm::vec2 mousePos() { return __instance__->mousePosImpl(); }

        // bind NULL to unbind
        static void bindWindow(Window* window) { __activeWindow__ = window; }

    private:
        virtual bool keyPressedImpl(const KeyCode_t& key) const = 0;
        virtual bool mouseButtonPressedImpl(const MouseCode_t& button) const = 0;
        virtual glm::vec2 mousePosImpl() const = 0;

    protected:
        // this holds the raw pointer of the active window (Scoped ptr)
        // it's safe since Input's method will only be called when the application is active
        // probably better to Scoped/Ref it, but I won't bother
        static Window* __activeWindow__;
    private:
        static Input* __instance__;
    };
}

#endif /* __INPUT_H__ */
