#ifndef __MAC_INPUT_H__
#define __MAC_INPUT_H__

#include "core/input/input.h"

namespace Engine7414
{
    class MacInput : public Input
    {
        bool keyPressedImpl(const KeyCode_t& key) const override;
        bool mouseButtonPressedImpl(const MouseCode_t& button) const override;
    };
}

#endif /* __MAC_INPUT_H__ */
