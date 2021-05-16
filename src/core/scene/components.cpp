#include "core/scene/components.h"
#include "core/app.h"

#include <glm/gtx/quaternion.hpp>

namespace Engine7414
{
    glm::mat4 TransformComponent::transform() const {
        return glm::translate(glm::mat4(1.0f), translation) *
               glm::toMat4(glm::quat({ glm::radians(rotation.x), glm::radians(rotation.y), glm::radians(rotation.z) })) *
               glm::scale(glm::mat4(1.0f), scale);
    }

    CameraComponent::CameraComponent(CameraBase::Type type, bool active, float aspect, float fov_or_size, float nearClip, float farClip) :
        active(active)
    {
        aspect = aspect > 0.0f ? aspect : App::getWindow()->AspectRatio();
        switch (type) {
            case CameraBase::Type::Orthographic: camera = Camera2D::create(fov_or_size, aspect, nearClip, farClip); break;
            // case CameraBase::Type::Perspective: camera = Camera3D::create(fov_or_size, aspect, nearClip, farClip); break;
            default: CORE_ASSERT(false, "");
        }
    }
}
