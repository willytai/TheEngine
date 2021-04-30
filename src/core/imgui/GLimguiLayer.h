#ifndef __GL_IMGUI_LAYER_H__
#define __GL_IMGUI_LAYER_H__

#include "core/imgui/imguiLayer.h"

namespace Engine7414
{
    class GLImGuiLayer : public ImGuiLayer
    {
    public:
        GLImGuiLayer();
        ~GLImGuiLayer();

        void begin() override;
        void end() override;
        void onAttach() override;
        void onDetach() override;
    };
}

#endif /* ifndef __GL_IMGUI_LAYER_H__ */
