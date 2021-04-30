#ifndef __IMGUI_LAYER_H__
#define __IMGUI_LAYER_H__

#include "core/layer/layer.h"
#include "backend/backend.h"
#include <imgui/imgui.h>

namespace Engine7414
{
    class ImGuiLayer : public Layer
    {
        static bool __blockEvents__;
        static ImGuiLayer* __instance__;
    public:
        ImGuiLayer();
        virtual ~ImGuiLayer();

        virtual void begin() = 0;
        virtual void end() = 0;
        virtual void onAttach() override = 0;
        virtual void onDetach() override = 0;
        void onEvent(Event& event) override;

        static inline void setBlockEvent() { __blockEvents__ = true; }
        static inline void setNoBlockEvent() { __blockEvents__ = false; }
        static void fontZoomIn();
        static void fontZoomOut();

        static ImGuiLayer* create(const RendererBackend& backend);

    private:
        void onKeyEvents(Event& event);
        void onMouseEvents(Event& event);
    };
}

#endif /* __IMGUI_LAYER_H__ */
