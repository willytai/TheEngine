#include "core/layer/layerStack.h"

namespace Engine7414
{
    LayerStack::LayerStack() {
        _insertID = 0;
    }

    LayerStack::~LayerStack() {
        for (auto* layer : _layer) delete layer;
    }

    void LayerStack::pushLayer(Layer* layer) {
        _layer.emplace( _layer.begin()+_insertID, layer );
        _insertID++;
        layer->onAttach();
    }

    void LayerStack::pushOverlay(Layer* layer) {
        _layer.emplace_back( layer );
        layer->onAttach();
    }

    void LayerStack::popLayer(Layer* layer) {
        auto it = std::find( _layer.begin(), _layer.begin()+_insertID, layer );
        if ( it != _layer.begin()+_insertID) {
            _layer.erase( it );
            _insertID--;
            layer->onDetach();
        }
    }

    void LayerStack::popOverlay(Layer* layer) {
        auto it = std::find( _layer.begin()+_insertID, _layer.end(), layer );
        if ( it != _layer.end() ) {
            _layer.erase( it );
            layer->onDetach();
        }
    }
}
