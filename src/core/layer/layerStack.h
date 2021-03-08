#ifndef __LAYER_STACK_H__
#define __LAYER_STACK_H__

#include "core/layer/layer.h"
#include <vector>

namespace Engine7414
{
    class LayerStack
    {
    public:
        typedef std::vector<Layer*> stack_t;
    public:
        LayerStack();
        ~LayerStack();

        void pushLayer(Layer* layer);
        void pushOverlay(Layer* layer);
        void popLayer(Layer* layer);
        void popOverlay(Layer* layer);

        inline stack_t::iterator begin() { return _layer.begin(); }
        inline stack_t::iterator end() { return _layer.end(); }
        inline stack_t::reverse_iterator rbegin() { return _layer.rbegin(); }
        inline stack_t::reverse_iterator rend() { return _layer.rend(); }

    private:
        stack_t         _layer;
        unsigned int    _insertID;
    };
}

#endif /* __LAYER_STACK_H__ */
