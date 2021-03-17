#ifndef __INPUT_H__
#define __INPUT_H__

#include "core/window.h"
#include "core/core.h"
#include "core/input/codes.h"

namespace Engine7414
{
    class Input
    {
    public:
        static bool keyPressed(KeyCode_t key) { return __instance__->keyPressedImpl(key); }
        static bool mouseButtonPressed(MouseCode_t button) { return __instance__->mouseButtonPressedImpl(button); }

        // bind NULL to unbind
        static void bindWindow(Window* window) { __activeWindow__ = window; }

    private:
        virtual bool keyPressedImpl(const KeyCode_t& key) const = 0;
        virtual bool mouseButtonPressedImpl(const MouseCode_t& button) const = 0;

    protected:
        static Window* __activeWindow__;
    private:
        static Input* __instance__;
    };
}

#endif /* __INPUT_H__ */