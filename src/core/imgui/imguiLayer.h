#ifndef __IMGUI_LAYER_H__
#define __IMGUI_LAYER_H__

#include "core/layer/layer.h"
#include "imgui/imgui.h"

namespace Engine7414
{
    class ImGuiLayer : public Layer
    {
    public:
        ImGuiLayer();
        ~ImGuiLayer();

        void begin();
        void end();
        void onAttach() override;
        void onDetach() override;
        void onImGui() override;
        void onEvent(Event& event) override;
    };
}

#endif /* __IMGUI_LAYER_H__ */
