#ifndef __COMPONENTS_H__
#define __COMPONENTS_H__

#include "core/renderer/camera.h"
#include "core/renderer/cameraController.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace Engine7414
{
    struct TagComponent
    {
        const char* tag;
    };

    struct TransformComponent
    {
        glm::vec3  translation = {0.0f, 0.0f, 0.0f};
        glm::vec3  scale = {1.0f, 1.0f, 1.0f};

        glm::mat4 transform() const;
    };

    struct SpriteRendererComponent
    {
        glm::vec4 color = {1.0f, 1.0f, 1.0f, 1.0f};
    };

    struct CameraComponent
    {
        Scoped<CameraBase>  camera;
        CameraController    controller;

        // default to false to avoid multiple active cameras during initialization
        bool active;

        CameraComponent(float aspect, CameraBase::Type type, bool active = false, bool controllable = false);
    };
}

#endif /* __COMPONENTS_H__ */
