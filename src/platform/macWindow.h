#ifndef __MAC_WINDOW_H__
#define __MAC_WINDOW_H__
#define GLFW_INCLUDE_NONE

#include "core/window.h"
#include <GLFW/glfw3.h>

namespace Engine7414
{
    struct windowData
    {
        int width;
        int height;
        bool vsync;
        Window::eventCallbackFn callback;
    };

    class MacWindow : public Window
    {
        static bool __glfwInitialized__;
    public:
        MacWindow(const char* title, int width, int height);
        ~MacWindow();

        /* access functions */
        inline int  getWidth()  const override { return _data.width; }
        inline int  getHeight() const override { return _data.height; }
        inline bool VSync()     const override { return _data.vsync; }

        /* setting functions */
        void setEventCallback(const eventCallbackFn& fn) override;
        void enableVSync() override;
        void disbaleVSync() override;

        /* other */
        void onUpdate() override;

    private:
        void shutdown();
        void setCallbacks();

    private:
        GLFWwindow* _glfwWindow;
        windowData  _data;
    };
}

#endif /* __MAC_WINDOW_H__ */
