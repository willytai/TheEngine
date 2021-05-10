#include "backend/MTL/MTLrenderAPI.h"
#include "backend/MTL/MTLcontext.h"
#include "core/renderer/renderer.h"
#include "core/core.h"

namespace Engine7414
{
    MTLRenderAPI* MTLRenderAPI::__instance__ = NULL;

    MTLRenderAPI::MTLRenderAPI() {
        if ( __instance__ ) {
            BACKEND_ASSERT( false, "multiple render API not supported" );
        }
        _handle = [[MTLRenderHandle alloc] init];
        __instance__ = this;
    }

    void MTLRenderAPI::init() const {
        // TODO
        // hard coding this for now, don't know the API to retrieve the information at runtime
        Renderer::setMaxTextSlot( 16 );
    }

    void MTLRenderAPI::setClearColor(const glm::vec4& color) const {
        [_handle setClearColorR:color.r G:color.g B:color.b A:color.a];
    }

    void MTLRenderAPI::clear() const {
        [_handle setClear];
    }

    void MTLRenderAPI::begin() const {
        [_handle beginWithContext:MTLContext::getContext()];
    }

    void MTLRenderAPI::end() const {
        [_handle end];
    }

    void MTLRenderAPI::drawElement(const Ref<VertexArray>& vertexArray, const uint32_t& indexCount) const {
    }

    void MTLRenderAPI::setViewPort(const uint32_t& x, const uint32_t& y, const uint32_t& width, const uint32_t& height) const {
    }

}
