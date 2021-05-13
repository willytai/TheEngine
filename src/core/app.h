#ifndef __APP_H__
#define __APP_H__

#include "core/core.h"
#include "core/window/window.h"
#include "core/event/event.h"
#include "core/layer/layerStack.h"
#include "core/imgui/imguiLayer.h"
#include "core/util/log.h"
#include "core/util/stopwatch.h"
#include "platform/platform.h"
#include "backend/backend.h"
#include <memory>

namespace Engine7414
{
    class App
    {
        static App* appInstancePtr;
    public:
        App(RendererBackend backend, const char* name = NULL, int verbosity = -1);
        virtual ~App();

        void run();
        void onEvent(Event& event);
        void pushLayer(Layer* layer);
        void pushOverlay(Layer* layer);

        inline static Window* getWindow() { return appInstancePtr->_window.get(); }
        inline static ImGuiLayer* getImGuiLayer() { return appInstancePtr->_imguiLayer; }
        static void close();

    private:
        bool onWindowClose(WindowCloseEvent& event);
        bool onWindowResize(WindowResizeEvent& event);
        bool onWindowIconify(WindowIconifyEvent& event);

    private:
        bool            _shouldRun;
        bool            _minimized;
        StopWatch       _stopWatch;
        ImGuiLayer*     _imguiLayer;
        LayerStack      _layerStack;
        Scoped<Window>  _window;
    };

    App* appCreate(int argc, char** argv);
}

#endif /* __APP_H__ */
