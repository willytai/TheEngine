#ifndef __GLFW_INPUT_H__
#define __GLFW_INPUT_H__

#include "core/input/input.h"

namespace Engine7414
{
    class GLFWInput : public Input
    {
        bool keyPressedImpl(const KeyCode_t& key) const override;
        bool mouseButtonPressedImpl(const MouseCode_t& button) const override;
        glm::vec2 mousePosImpl() const override;
    };
}

#endif /* __GLFW_INPUT_H__ */
