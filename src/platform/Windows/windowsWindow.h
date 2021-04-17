#pragma once

#include "core/window/window.h"
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

    class WindowsWindow : public Window
    {
        static bool __glfwInitialized__;
    public:
        WindowsWindow(const WindowProps& props);
        ~WindowsWindow();

        /* access functions */
        inline int   getWidth()  const override { return _data.width; }
        inline int   getHeight() const override { return _data.height; }
        inline bool  VSync()     const override { return _data.vsync; }
        inline void* nativeWindow()    override { return (void*)_glfwWindow; }
        inline void* nativeDevice()    override { return NULL; }

        /* setting functions */
        void setEventCallback(const eventCallbackFn& fn) override;
        void enableVSync() override;
        void disbaleVSync() override;

        /* other */
        void onUpdate() override;

    private:
        void createContext(const RendererBackend& backend);
        void shutdown();
        void setCallbacks();

    private:
        GLFWwindow* _glfwWindow;
        windowData  _data;
    };
}
