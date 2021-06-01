#include "platform/glfwInput.h"
#include "platform/glfwTypes.h"

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

// glfw key codes has the exact same value as those define in core/input/input.h
// It's OK to use them directly as long as they are casted to the correct type

namespace Engine7414
{
    // inputs will be captured through GLFW
    Input* Input::__instance__ = new GLFWInput;

    bool GLFWInput::keyPressedImpl(const KeyCode_t& key) const {
        CORE_ASSERT( __activeWindow__ != NULL,
                     "Did you forget to bind the window with the Input class before Input Polling?" );
        auto window = (GLFWwindow*)__activeWindow__->nativeWindow();
        return glfwGetKey( window, (GLFW_KEY_CODE_t)key ) != GLFW_RELEASE;
    }

    bool GLFWInput::mouseButtonPressedImpl(const MouseCode_t& button) const {
        CORE_ASSERT( __activeWindow__ != NULL,
                     "Did you forget to bind the window with the Input class before Input Polling?" );
        auto window = (GLFWwindow*)__activeWindow__->nativeWindow();
        return glfwGetMouseButton( window, (GLFW_MOUSE_BUTTON_t)button ) != GLFW_RELEASE;
    }

    glm::vec2 GLFWInput::mousePosImpl() const {
        CORE_ASSERT(__activeWindow__ != NULL,
            "Did you forget to bind the window with the Input class before Input Polling?");
        double x, y;
        auto window = (GLFWwindow*)__activeWindow__->nativeWindow();
        glfwGetCursorPos(window, &x, &y);
        return glm::vec2{(float)x, (float)y};
    }
}
