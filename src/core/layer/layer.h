#ifndef __LAYER_H__
#define __LAYER_H__

#include "core/event/event.h"
#include <string>

namespace Engine7414
{
    class Layer
    {
    public:
        Layer(const char* name = "default layer");
        virtual ~Layer();

        virtual void onAttach() {};
        virtual void onDetach() {};
        virtual void onUpdate() {};
        virtual void onImGui() {};
        virtual void onEvent(Event& event) {};

        inline const char* name() const { return _debug_name.c_str(); }

    private:
        std::string _debug_name;
    };
}

#endif /* __LAYER_H__ */
