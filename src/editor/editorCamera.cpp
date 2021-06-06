#include "editor/editorCamera.h"
#include "core/input/input.h"

namespace Engine7414
{
    Scoped<EditorCamera> EditorCamera::create(float fov, float aspect, float nearClip, float farClip) {
        fov = fov > 0.0f ? fov : 45.0f;
        nearClip = nearClip > 0.0f ? nearClip : 1.0f;
        farClip = farClip > 1.0f ? farClip : 1000.0f;
        return CreateScoped<EditorCamera>(fov, aspect, nearClip, farClip);
    }

    Scoped<EditorCamera> EditorCamera::create() {
        return EditorCamera::create(45.0f, 1.333f, 0.1f, 1000.0f);
    }

    EditorCamera::EditorCamera(float fov, float aspect, float nearClip, float farClip) {
        params = { fov, aspect, nearClip, farClip };
    }

    void EditorCamera::onUpdate(const TimeStep& deltaTime) {
        if (Input::keyPressed(Key::LEFT_ALT)) {
            glm::vec2 newMousePos = Input::mousePos();
            glm::vec2 deltaMouse = (newMousePos - _initMousePos) * 0.003f;
            _initMousePos = newMousePos;

            if (Input::mouseButtonPressed(Mouse::BUTTON_MIDDLE)) this->mouseDrag(deltaMouse);
            else if (Input::mouseButtonPressed(Mouse::BUTTON_LEFT)) this->mouseRotate(deltaMouse);
            else if (Input::mouseButtonPressed(Mouse::BUTTON_RIGHT)) this->mouseZoom(deltaMouse.y);
        }
    }

    void EditorCamera::onEvent(Event& event) {
        EventDispatcher dispatcher(event);
        dispatcher.dispatch<MouseScrolledEvent>(CORE_BIND_EVENT_FN(EditorCamera::onMouseScrolled));
    }

    const glm::mat4& EditorCamera::getViewProjection() {
        bool updateCache = __updateProj || __updateView;
        if (__updateProj) this->updateProjMatrix();
        if (__updateView) this->updateViewMatrix();
        if (updateCache) __m_view_proj = __m_projection * __m_view;
        return __m_view_proj;
    }

    const glm::mat4& EditorCamera::getView() {
        if (__updateView) this->updateViewMatrix();
        return __m_view;
    }

    const glm::mat4& EditorCamera::getProjection() {
        if (__updateProj) this->updateProjMatrix();
        return __m_projection;
    }

    void EditorCamera::updateProjMatrix() const {
        __m_projection = glm::perspective(glm::radians(params.fov),
            params.aspect,
            params.nearClip,
            params.farClip);
        __updateProj = false;
    }

    void EditorCamera::updateViewMatrix() {
        this->updatePosition();
        __m_view = glm::translate(glm::mat4(1.0f), _position) * glm::toMat4(this->orientation());
        __m_view = glm::inverse(__m_view);
        __updateView = false;
    }

    void EditorCamera::updatePosition() {
        _position = _focalPoint - _distance * this->forwardDirection();
    }

    bool EditorCamera::onMouseScrolled(MouseScrolledEvent& event) {
        this->mouseZoom(event.yOffset() * 0.1f);
        __updateView = true;
        return false;
    }

    glm::vec3 EditorCamera::forwardDirection() {
        // rotate the z axis with the camera
        return glm::rotate(this->orientation(), glm::vec3(0.0f, 0.0f, -1.0f));
    }

    glm::vec3 EditorCamera::upDirection() {
        // rotate the y axis with the camera
        return glm::rotate(this->orientation(), glm::vec3(0.0f, 1.0f, 0.0f));
    }

    glm::vec3 EditorCamera::leftDirection() {
        return glm::rotate(this->orientation(), glm::vec3(-1.0f, 0.0f, 0.0f));
    }

    glm::quat EditorCamera::orientation() {
        // Why negatvie though?
        return glm::quat(glm::vec3(-_pitch, -_yaw, 0.0f));
    }

    void EditorCamera::mouseDrag(const glm::vec2& deltaMouse) {
        // the further away, the faster it moves
        auto [xSpeed, ySpeed] = this->dragSpeed();
        _focalPoint += this->leftDirection() * deltaMouse.x * _distance * xSpeed;
        _focalPoint += this->upDirection() * deltaMouse.y * _distance * ySpeed;
        __updateView = true;
    }

    void EditorCamera::mouseRotate(const glm::vec2& deltaMouse) {
        float yawSign = this->upDirection().y < 0 ? -1.0f : 1.0f;
        _yaw += yawSign * deltaMouse.x * 0.8f;
        _pitch += deltaMouse.y * 0.8f;
        __updateView = true;
    }

    void EditorCamera::mouseZoom(const float& zoom) {
        // moving the camera along the front axis instead of changing the fov
        _distance -= zoom * this->zoomSpeed();
        if (_distance < 1.0f) {
            _focalPoint += this->forwardDirection();
            _distance = 1.0f;
        }
        __updateView = true;
    }

    float EditorCamera::zoomSpeed() {
        // making it proportional to the squared-distance to the focal point
        float dist = _distance * 0.2f;
        dist = std::max(dist, 0.0f);
        float speed = dist * dist;
        return std::min(speed, 100.0f);
    }

    std::pair<float, float> EditorCamera::dragSpeed() {
        float x = std::min(_viewportSize.x / 1000.0f, 2.4f);
        float xSpeed = 0.0366f * (x * x) - 0.1778f * x + 0.4021f;
        float y = std::min(_viewportSize.y / 1000.0f, 2.4f);
        float ySpeed = 0.0366f * (y * y) - 0.1778f * y + 0.4021f;
        return { xSpeed, ySpeed };
    }
}