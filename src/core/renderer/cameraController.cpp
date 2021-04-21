#include "core/renderer/cameraController.h"
#include "core/renderer/renderer.h"
#include "core/input/input.h"

namespace Engine7414
{
    CameraController::CameraController(CameraBase::Type type)
        : _translationSpeed(5.0f),
          _rotationSpeed(30.0f),
          _zoomLevel(1.0f)

    {
        switch (type) {
            case CameraBase::Orthographic:
            {
                onUpdate_func = std::bind(&CameraController::onUpdate2D, this, std::placeholders::_1, std::placeholders::_2);
                rendererUpdate_func = std::bind(&Renderer2D::setUpdateMatFlag);
                break;
            }
            case CameraBase::Perspective:
            {
                onUpdate_func = std::bind(&CameraController::onUpdate3D, this, std::placeholders::_1, std::placeholders::_2);
                rendererUpdate_func = std::bind(&Renderer::setUpdateMatFlag);
                break;
            }
            default:
            {
                CORE_ASSERT(false, "{} Not Implemented!", __PRETTY_FUNCTION__);
            }
        }
    }

    void CameraController::bind(CameraBase* camera) {
        _camera = camera;
    }

    void CameraController::onUpdate(const TimeStep& deltaTime, glm::vec3& position) {
        if (_camera) {
            onUpdate_func(deltaTime, position);
        }
    }

    void CameraController::onUpdate2D(const TimeStep& deltaTime, glm::vec3& position) {
        if (Input::keyPressed(Key::W)) {
            this->moveY(position, _translationSpeed * deltaTime);
        }
        else if (Input::keyPressed(Key::S)) {
            this->moveY(position, -_translationSpeed * deltaTime);
        }
        if (Input::keyPressed(Key::D)) {
            this->moveX(position, _translationSpeed * deltaTime);
        }
        else if (Input::keyPressed(Key::A)) {
            this->moveX(position, -_translationSpeed * deltaTime);
        }
    }

    void CameraController::onUpdate3D(const TimeStep& deltaTime, glm::vec3& position) {
        CORE_ASSERT(false, "{} Not Implemented!", __PRETTY_FUNCTION__);
    }

    void CameraController::moveX(glm::vec3& position, const float& dist) {
        rendererUpdate_func();
        position.x += dist;
    }

    void CameraController::moveY(glm::vec3& position, const float& dist) {
        rendererUpdate_func();
        position.y += dist;
    }

    void CameraController::moveZ(glm::vec3& position, const float& dist) {
        rendererUpdate_func();
        position.z += dist;
    }

    void CameraController::onEvent(Event& event) {
        EventDispatcher dispatcher(event);
        dispatcher.dispatch<WindowResizeEvent>(CORE_BIND_EVENT_FN(CameraController::onWindowResize));
        dispatcher.dispatch<MouseScrolledEvent>(CORE_BIND_EVENT_FN(CameraController::onMouseScrolled));
    }

    void CameraController::onResize(const float& width, const float& height) {
        rendererUpdate_func();
        _camera->setAspectRatio(width/height);
    }

    bool CameraController::onWindowResize(WindowResizeEvent& event) {
        this->onResize((float)event.width(), (float)event.height());
        return false;
    }

    bool CameraController::onMouseScrolled(MouseScrolledEvent& event) {
        rendererUpdate_func();
        _zoomLevel -= event.yOffset() * 0.1f;
        CLIP_BETWEEN(_zoomLevel, 0.1f, std::numeric_limits<float>::max());
        _camera->zoom(_zoomLevel);
        return false;
    }

    // move the clip stuff to controller (3D)
    // void Camera::changeFOV(float deltaFovDeg) {
    //     __updateProj = true;
    //     __params.fov += deltaFovDeg;
    //     CLIP_BETWEEN(__params.fov, CameraBase::FOV_MIN, CameraBase::FOV_MAX);
    // }
}
