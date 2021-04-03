#include "core/renderer/cameraController.h"
#include "core/input/Input.h"

namespace Engine7414
{
	CameraController::CameraController()
		: _translationSpeed(10.0f),
		  _rotationSpeed(30.0f),
		  _zoomLevel(1.0f)

	{
		_camera.reset();
		onUpdate_func = [](const TimeStep& deltaTime) { CORE_ASSERT(false, "camera not set in CameraController!"); };
	}

	void CameraController::createCamera2D(const float& aspect) {
		CORE_ASSERT(!_camera, "camera already exists!");
		_camera = Camera2D::create(-aspect*_zoomLevel, aspect*_zoomLevel, -_zoomLevel, _zoomLevel);
		onUpdate_func = std::bind(&CameraController::onUpdate2D, this, std::placeholders::_1);
	}

	void CameraController::createCamera3D(const float& aspect, const float& FovDeg, const float& nearClip, const float& farClip) {
		CORE_ASSERT("{} Not Implemented!", __PRETTY_FUNCTION__);
	}

	void CameraController::onUpdate(const TimeStep& deltaTime) {
		onUpdate_func(deltaTime);
	}

	void CameraController::onUpdate2D(const TimeStep& deltaTime) {
        if (Engine7414::Input::keyPressed(Engine7414::Key::W)) {
            _camera->moveY(1.0f * deltaTime);
        }
        else if (Engine7414::Input::keyPressed(Engine7414::Key::S)) {
            _camera->moveY(-1.0f * deltaTime);
        }
        if (Engine7414::Input::keyPressed(Engine7414::Key::D)) {
            _camera->moveX(1.0f * deltaTime);
        }
        else if (Engine7414::Input::keyPressed(Engine7414::Key::A)) {
            _camera->moveX(-1.0f * deltaTime);
        }
	}

	void CameraController::onUpdate3D(const TimeStep& deltaTime) {
		CORE_ASSERT(false, "{} Not Implemented!", __PRETTY_FUNCTION__);
	}

	void CameraController::onEvent(Event& event) {
		EventDispatcher dispatcher(event);
		dispatcher.dispatch<WindowResizeEvent>(CORE_BIND_EVENT_FN(CameraController::onWindowResize));
		dispatcher.dispatch<MouseScrolledEvent>(CORE_BIND_EVENT_FN(CameraController::onMouseScrolled));
	}

	bool CameraController::onWindowResize(WindowResizeEvent& event) {
		_camera->setAspectRatio((float)event.width()/(float)event.height());
		return false;
	}

	bool CameraController::onMouseScrolled(MouseScrolledEvent& event) {
		_zoomLevel -= event.yOffset() * 0.1f;
		CLIP_BETWEEN(_zoomLevel, 0.1f, std::numeric_limits<float>::max());
		_camera->zoom(_zoomLevel);
		return false;
	}

	// move the clip stuff to controller (3D)
	// void Camera::changeFOV(float deltaFovDeg) {
	// 	__updateProj = true;
	// 	__params.fov += deltaFovDeg;
	// 	CLIP_BETWEEN(__params.fov, CameraBase::FOV_MIN, CameraBase::FOV_MAX);
	// }
}