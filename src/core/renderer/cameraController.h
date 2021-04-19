#ifndef __CAMERA_CONTROLLER_H__
#define __CAMERA_CONTROLLER_H__

#include "core/renderer/camera.h"
#include "core/util/timeStep.h"
#include "core/event/event.h"

namespace Engine7414
{
    class CameraController
    {
    public:
        CameraController(CameraBase::Type type);
        ~CameraController() = default;

        void bind(CameraBase* camera);

        void onUpdate(const TimeStep& deltaTime, glm::vec3& position);
        void onEvent(Event& event);
        void onResize(const float& width, const float& height);

    private:
        void onUpdate2D(const TimeStep& deltaTime, glm::vec3& position);
        void onUpdate3D(const TimeStep& deltaTime, glm::vec3& position);
        void moveX(glm::vec3& position, const float& dist);
        void moveY(glm::vec3& position, const float& dist);
        void moveZ(glm::vec3& position, const float& dist);

    private:
        bool onWindowResize(WindowResizeEvent& event);
        bool onMouseScrolled(MouseScrolledEvent& event);

    private:
        float            _translationSpeed;
        float            _rotationSpeed;

        // this is for orthographic camera
        float            _zoomLevel;

        std::function<void(const TimeStep&, glm::vec3&)> onUpdate_func;
        std::function<void()> rendererUpdate_func;

        // holds a weak reference
        // the owner of the camera is the CameraComponent
        CameraBase*    _camera = nullptr;
    };
}
#endif
