#include "core/renderer/camera.h"

namespace Engine7414
{
    float CameraBase::FOV_MIN = 1.0f;
    float CameraBase::FOV_MAX = 60.0f;

    /*********************/
    /* Camera Base Class */
    /*********************/
    CameraBase::CameraBase()
        : __position(0.0f, 0.0f, 0.0f, 1.0f),
          __updateProj(true),
          __updateView(true),
          __m_projection(glm::mat4(1.0f)),
          __m_view(glm::mat4(1.0f)),
          __m_ProjViewCache(glm::mat4(1.0f))
    {}

    void CameraBase::setPosition(const glm::vec4& pos) {
        CORE_ERROR( "{} not supported for your camera!", __FUNCSIG__ );
    }

    void CameraBase::setPosition(const glm::vec3& pos) {
        CORE_ERROR("{} not supported for your camera!", __FUNCSIG__);
    }

    void CameraBase::moveX(const float& dist) {
        __updateView = true;
        __position.x += dist;
    }

    void CameraBase::moveY(const float& dist) {
        __updateView = true;
        __position.y += dist;
    }

    void CameraBase::moveZ(const float& dist) {
        __updateView = true;
        __position.z += dist;
    }

    const glm::mat4& CameraBase::projXview() const {
        if (!__updateProj && !__updateView) return __m_ProjViewCache;
        if (__updateProj) this->updateProjMatrix();
        if (__updateView) this->updateViewMatrix();
        __m_ProjViewCache = __m_projection * __m_view;
        return __m_ProjViewCache;
    }

    /**************************************/
    /* 3D Camera (Perspective Projection) */
    /**************************************/
    Camera::Camera(float FovDeg, float aspect, float nearClip, float farClip)
        : __front(0.0f, 0.0f, -1.0f, 0.0f),
          __rotation({ 0.0f, 0.0f }),
          __params({ FovDeg, aspect, nearClip, farClip })
    {}

    void Camera::setAspectRatio(const float& aspect) {
        __updateProj = true;
        __params.aspect = aspect;
    }

    void Camera::setPosition(const glm::vec4& pos) {
        __updateView = true;
        __position = pos;
    }

    void Camera::setPosition(const glm::vec3& pos) {
        __updateView = true;
        __position = glm::vec4( pos, 1.0f );
    }

    void Camera::setFOV(float fov) {
        __updateProj = true;
        __params.fov = fov;
        CLIP_BETWEEN( __params.fov, CameraBase::FOV_MIN, CameraBase::FOV_MAX );
    }

    void Camera::setYaw(float YawDeg) {
        this->rotateY( YawDeg - __rotation.yaw );
    }

    void Camera::setPitch(float PitchDeg) {
        this->rotateX( PitchDeg - __rotation.pitch );
    }

    void Camera::zoom(const float& fov) {
        __updateProj = true;
        __params.fov = fov;
    }

    void Camera::rotateY(float deltaYawDeg) {
        __updateView = true;
        __rotation.yaw += deltaYawDeg;
        __front = glm::rotate( glm::mat4(1.0f), glm::radians(deltaYawDeg), glm::vec3(0.0f, 1.0f, 0.0f) )*__front;
    }

    void Camera::rotateX(float deltaPitchDeg) {
        __updateView = true;
        __rotation.pitch += deltaPitchDeg;
        __front = glm::rotate( glm::mat4(1.0f), glm::radians(deltaPitchDeg), glm::vec3(1.0f, 0.0f, 0.0f) )*__front;
    }

    void Camera::updateViewMatrix() const {
        __m_view = glm::lookAt( __position.xyz(),
                                (__position+__front).xyz(),
                                glm::vec3(0.0f, 1.0f, 0.0f) );
        __updateView = false;
    }

    void Camera::updateProjMatrix() const {
        __m_projection = glm::perspective( glm::radians(__params.fov),
                                           __params.aspect,
                                           __params.nearClip,
                                           __params.farClip );
        __updateProj = false;
    }

    /***************************************/
    /* 2D Camera (Orthographic Projection) */
    /***************************************/
    Ref<Camera2D> Camera2D::create(float left, float right, float bottom, float top) {
        return CreateRef<Camera2D>(left, right, bottom, top);
    }

    Camera2D::Camera2D(float left, float right, float bottom, float top)
        : __rotation(0.0f),
          __aspect((right-left) / (top-bottom)),
          __params({ left, right, bottom, top })
    {}

    void Camera2D::setAspectRatio(const float& aspect) {
        __updateProj = true;
        __params.left = aspect * __params.bottom;
        __params.right = aspect * __params.top;
    }

    void Camera2D::setPosition(const glm::vec3& pos) {
        __updateView = true;
        __position = glm::vec4(pos, 1.0f);
    }

    void Camera2D::setRotation(const float& rotation) {
        __updateView = true;
        __rotation = rotation;
    }

    void Camera2D::zoom(const float& level) {
        __updateProj = true;
        __params.left   = -__aspect * level;
        __params.right  = __aspect * level;
        __params.bottom = -level;
        __params.top    = level;
    }

    void Camera2D::updateViewMatrix() const {
        glm::mat4 transform = glm::translate(glm::mat4(1.0f), __position.xyz())
                            * glm::rotate(glm::mat4(1.0f), glm::radians(__rotation), glm::vec3(0.0f, 0.0f, 1.0f));
        __m_view = glm::inverse(transform);
        __updateView = false;
    }

    void Camera2D::updateProjMatrix() const {
        __m_projection = glm::ortho(__params.left, __params.right, __params.bottom, __params.top, -1.0f, 1.0f);
        __updateProj = false;
    }
}
