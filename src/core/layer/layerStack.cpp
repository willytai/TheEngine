#include "core/layer/layerStack.h"

namespace Engine7414
{
    LayerStack::LayerStack() {
        _layerInsert_it = _layer.end();
    }

    LayerStack::~LayerStack() {
        for (auto* layer : _layer) delete layer;
    }

    void LayerStack::pushLayer(Layer* layer) {
        _layerInsert_it = _layer.emplace( _layerInsert_it, layer );
        _layerInsert_it++;
    }

    void LayerStack::pushOverlay(Layer* layer) {
        _layer.emplace_back( layer );
    }

    void LayerStack::popLayer(Layer* layer) {
        auto it = std::find( _layer.begin(), _layerInsert_it, layer );
        if ( it != _layerInsert_it ) {
            _layer.erase( it );
            _layerInsert_it--;
        }
    }

    void LayerStack::popOverlay(Layer* layer) {
        auto it = std::find( _layerInsert_it, _layer.end(), layer );
        if ( it != _layer.end() ) {
            _layer.erase( it );
        }
    }
}
