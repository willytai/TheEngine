#ifndef __RENDERER2D_H__
#define __RENDERER2D_H__

#include "core/renderer/camera.h"
#include "core/renderer/shader.h"
#include "core/renderer/vertexArray.h"
#include "core/renderer/texture.h"

namespace Engine7414
{
    class Renderer2D
    {
    public:
        static void init();
        static void shutdown();

        static void beginScene(const Ref<CameraBase>& camera, const glm::vec4& color = { 0.0f, 0.0f, 0.0f, 1.0f });
        static void endScene();
        static void flush();

        // position stands for the center of the quad
        // TODO tiling effect!
        static void drawQuad(const glm::vec2& position, const glm::vec2& size, const glm::vec4& color);
        static void drawQuad(const glm::vec3& position, const glm::vec2& size, const glm::vec4& color);
        static void drawQuad(const glm::vec2& position, const glm::vec2& size, const Ref<Texture2D>& texture);
        static void drawQuad(const glm::vec3& position, const glm::vec2& size, const Ref<Texture2D>& texture);

        // TODO drawRotatedQuad!

    private:
        static void drawQuad(const glm::vec3& position, const glm::vec2& size, const glm::vec4& color, const Ref<Texture2D>& texture);
    };
}

#endif
