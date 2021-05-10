#ifndef __MTL_RENDER_H__
#define __MTL_RENDER_H__

#import "backend/MTL/MetalRenderAPI.h"

#include "core/renderer/renderAPI.h"

namespace Engine7414
{
    class MTLRenderAPI : public RenderAPI
    {
        static MTLRenderAPI* __instance__;
    public:
        static MTLRenderHandle* getRenderHandle() { return __instance__->_handle; }

    public:
        MTLRenderAPI();
        ~MTLRenderAPI() {}
        void init() const override;
        void clear() const override;
        void setClearColor(const glm::vec4& color) const override;
        void drawElement(const Ref<VertexArray>& vertexArray, const uint32_t& indexCount = 0) const override;
        void setViewPort(const uint32_t& x, const uint32_t& y, const uint32_t& width, const uint32_t& height) const override;


        void begin() const override;
        void end() const override;

        RendererBackend backend() const override { return RendererBackend::Metal; }

    private:
        MTLRenderHandle* _handle = nil;
    };
}

#endif /* __MTL_RENDER_H__ */
