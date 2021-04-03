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
        CameraController();
        ~CameraController() = default;

        void createCamera2D(const float& aspect);
        void createCamera3D(const float& aspect, const float& FovDeg, const float& nearClip = 0.1f, const float& farClip = 100.0f);

        inline Ref<CameraBase> getCamera() { return _camera; }

        void onUpdate(const TimeStep& deltaTime);
        void onEvent(Event& event);

    private:
        void onUpdate2D(const TimeStep& deltaTime);
        void onUpdate3D(const TimeStep& deltaTime);

    private:
        bool onWindowResize(WindowResizeEvent& event);
        bool onMouseScrolled(MouseScrolledEvent& event);

    private:
        float            _translationSpeed;
        float            _rotationSpeed;

        // this is for orthographic camera
        float            _zoomLevel;

        std::function<void(const TimeStep&)> onUpdate_func;

        Ref<CameraBase>    _camera;
    };
}
#endif
