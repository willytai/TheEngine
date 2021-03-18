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
        App(RendererBackend backend, int verbosity = -1);
        virtual ~App();

        void run();
        void onEvent(Event& event);
        void pushLayer(Layer* layer);
        void pushOverlay(Layer* layer);

        inline static Window* getWindow() { return appInstancePtr->_window.get(); }

    private:
        bool onWindowClose(WindowCloseEvent& e);
        bool onWindowResize(WindowResizeEvent& e);
        bool onWindowIconify(WindowIconifyEvent& e);

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
