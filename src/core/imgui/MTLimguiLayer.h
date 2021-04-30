#ifndef __MTL_IMGUI_LAYER_H__
#define __MTL_IMGUI_LAYER_H__

#include "core/imgui/imguiLayer.h"

namespace Engine7414
{
    class MTLImGuiLayer : public ImGuiLayer
    {
    public:
        MTLImGuiLayer();
        ~MTLImGuiLayer();

        void begin() override;
        void end() override;
        void onAttach() override;
        void onDetach() override;
    };
}

#endif /* ifndef __MTL_IMGUI_LAYER_H__ */
