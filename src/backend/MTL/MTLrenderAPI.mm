#import "backend/MTL/MTLrenderAPI.h"

#include "core/core.h"
#include "core/renderer/renderer.h"

#import <Metal/Metal.h>

namespace Engine7414
{
    void MTLRenderAPI::init() const {
        // TODO
        // hard coding this for now, don't know the API to retrieve the information at runtime
        Renderer::setMaxTextSlot( 16 );
    }

    void MTLRenderAPI::setViewPort(const uint32_t& x, const uint32_t& y, const uint32_t& width, const uint32_t& height) const {
    }

    void MTLRenderAPI::setClearColor(const glm::vec4& color) const {
    }

    void MTLRenderAPI::clear() const {
    }

    void MTLRenderAPI::drawElement(const Ref<VertexArray>& vertexArray, const uint32_t& indexCount) const {
    }

}
