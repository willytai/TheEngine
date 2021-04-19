#include "core/scene/components.h"

namespace Engine7414
{
    glm::mat4 TransformComponent::transform() const {
        return glm::translate(glm::mat4(1.0f), translation) *
            // glm::rotate( glm::mat4(1.0f), ... ) *
            glm::scale(glm::mat4(1.0f), scale);
    }

    CameraComponent::CameraComponent(float aspect, CameraBase::Type type, bool active, bool controllable) :
        controller(type),
        active(active)
    {
        camera = Camera2D::create(-aspect * 1.0f, aspect * 1.0f, -1.0f, 1.0f);
        if (controllable) {
            controller.bind(camera.get());
        }
    }
}