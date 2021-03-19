#ifndef __LAYER_H__
#define __LAYER_H__

#include "core/event/event.h"
#include "core/util/timeStep.h"
#include <string>

#if defined(__clang__)
    #pragma clang diagnostic push
    #pragma clang diagnostic ignored "-Wunused-parameter"
#elif defined(__GNUC__)
    #pragma GCC diagnostic push
    #pragma GCC diagnostic ignored "-Wunused-parameter"
#elif defined(_MSC_VER)
    #pragma warning(push)
#else
    #error "Compiler Not Supported!"
#endif

namespace Engine7414
{
    class Layer
    {
    public:
        Layer(const char* name = "default layer");
        virtual ~Layer();

        virtual void onAttach() {};
        virtual void onDetach() {};
        virtual void onUpdate(const TimeStep& deltaTime) {};
        virtual void onImGui() {};
        virtual void onEvent(Event& event) {};

        inline const char* name() const { return _debug_name.c_str(); }

    private:
        std::string _debug_name;
    };
}

#if defined(__clang__)
    #pragma clang diagnostic pop
#elif defined(__GNUC__)
    #pragma GCC diagnostic pop
#elif defined(_MSC_VER)
    #pragma warning(pop)
#else
    #error "Compiler Not Supported!"
#endif

#endif /* __LAYER_H__ */
