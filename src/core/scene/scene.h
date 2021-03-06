#ifndef __SCENE_H__
#define __SCENE_H__

#include "core/util/timeStep.h"
#include "core/event/event.h"
#include "core/core.h"
#include "core/renderer/framebuffer.h"
#include "editor/editorCamera.h"

#if defined(__clang__)
    #pragma clang diagnostic push
    #pragma clang diagnostic ignored "-Wsign-conversion"
#elif defined(__GNUC__)
    #pragma GCC diagnostic push
    #pragma GCC diagnostic ignored "-Wsign-conversion"
#elif defined(_MSC_VER)
    #pragma warning(push)
    #pragma warning(disable : 4819)
#else
    #error "Compiler Not Supported!"
#endif

#include <entt/entt.hpp>

#if defined(__clang__)
    #pragma clang diagnostic pop
#elif defined(__GNUC__)
    #pragma GCC diagnostic pop
#elif defined(_MSC_VER)
    #pragma warning(pop)
#else
    #error "Compiler Not Supported!"
#endif

namespace Engine7414
{
    class Entity;
    class Scene
    {
        friend class Entity;
        friend class Serializer;
        friend class HierarchyPanel;
        friend class Renderer;
    public:
        Scene();
        ~Scene();

        // API
        Entity createEntity(const char* name = NULL);
        float aspectRatio() const { return _sceneWidth / _sceneHeight; }

        void onUpdate(const TimeStep& deltaTime, const bool& viewportFocused = true);
        void onUpdateEditor(const TimeStep& deltaTime, Ref<EditorCamera>& camera, const Ref<FrameBuffer>& currentFrameBuffer);
        void onResize(const float& width, const float& height);
        void onEvent(Event& event);

        Entity getActiveCameraEntity();
        Entity getDirectionalLightEntity();
        std::string& getFilePath() { return saveFilePath; }
        void setFilePath(const char* path) { saveFilePath = std::string(path); }

        static Ref<Scene> create();

    private:
        entt::registry _registry;

        // -- lighting stuffs --
        entt::entity _directionalLightEntity;
        float  _ambientStrength = 0.1f;
        float  _specularStrength = 0.5;
        int    _shininess = 1;

        // these two are just used for camera component creation
        float _sceneWidth = 0.0f;
        float _sceneHeight = 0.0f;

        std::string saveFilePath = "";
    };
}

#endif /* __SCENE_H__ */
