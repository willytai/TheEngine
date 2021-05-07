#ifndef __RENDERER2D_H__
#define __RENDERER2D_H__

#include "core/renderer/camera.h"
#include "core/renderer/shader.h"
#include "core/renderer/vertexArray.h"
#include "core/renderer/texture.h"
#include "core/scene/components.h"

namespace Engine7414
{
    class Renderer2D
    {
        static glm::mat4 __ProjViewMatCache__;
        static bool __updateProjViewMat__;
    public:
        static void setUpdateMatFlag();

        static void init();
        static void shutdown();

        // for test
        static void beginTest(const glm::vec4& color = {0.0f, 0.0f, 0.0f, 1.0f});
        static void endTest();

        static void beginScene(const TransformComponent& transformComponent, const CameraBase* camera,  const glm::vec4& color = { 0.0f, 0.0f, 0.0f, 1.0f });
        static void endScene();
        static void flush();

        // position stands for the center of the quad
        // TODO tiling effect!
        static void drawQuad(const glm::vec2& position, const glm::vec2& size, const glm::vec4& color);
        static void drawQuad(const glm::vec3& position, const glm::vec2& size, const glm::vec4& color);
        static void drawQuad(const glm::vec2& position, const glm::vec2& size, const Ref<Texture2D>& texture);
        static void drawQuad(const glm::vec3& position, const glm::vec2& size, const Ref<Texture2D>& texture);
        static void drawQuad(const glm::mat4& transform, const glm::vec4& color);
        // static void drawQuad(const glm::mat4& transform, const Ref<Texture2D>& texture);

        // TODO drawRotatedQuad!

        struct statistics
        {
            uint32_t drawCalls = 0;
            uint32_t quadCount = 0;
            void reset() { drawCalls = quadCount = 0; }
        };
        static statistics stat();
        static void resetStat();

    private:
        static void drawQuad(const glm::vec3& position, const glm::vec2& size, const glm::vec4& color, const Ref<Texture2D>& texture);
        static void drawQuad(const glm::mat4& transform, const glm::vec4& color, const Ref<Texture2D>& texture);
    };
}

#endif
