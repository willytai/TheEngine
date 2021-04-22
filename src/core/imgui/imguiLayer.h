#ifndef __IMGUI_LAYER_H__
#define __IMGUI_LAYER_H__

#include "core/layer/layer.h"
#include <imgui/imgui.h>

namespace Engine7414
{
    class ImGuiLayer : public Layer
    {
        static bool __blockEvents__;
        static ImGuiLayer* __instance__;
    public:
        ImGuiLayer();
        ~ImGuiLayer();

        void begin();
        void end();
        void onAttach() override;
        void onDetach() override;
        void onEvent(Event& event) override;

        static inline void setBlockEvent() { __blockEvents__ = true; }
        static inline void setNoBlockEvent() { __blockEvents__ = false; }
        static void fontZoomIn();
        static void fontZoomOut();

    private:
        void onKeyEvents(Event& event);
        void onMouseEvents(Event& event);
    };
}

#endif /* __IMGUI_LAYER_H__ */
