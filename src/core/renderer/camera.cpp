#include "core/renderer/camera.h"

namespace Engine7414
{
    float Camera::FOV_MIN = 1.0f;
    float Camera::FOV_MAX = 60.0f;

    Camera::Camera(float FovDeg, float aspect, float nearClip, float farClip)
        : __position(0.0f, 0.0f, 0.0f, 1.0f),
          __front(0.0f, 0.0f, -1.0f, 0.0f),
          __rotation({ 0.0f, 0.0f }),
          __updateProj(true),
          __updateView(true),
          __m_projection(glm::mat4(1.0f)),
          __m_view(glm::mat4(1.0f)),
          __m_ProjViewCache(glm::mat4(1.0f)),
          __params({ FovDeg, aspect, nearClip, farClip })
    {}

    Camera::~Camera() {}

    void Camera::setAspect(float width, float height) {
        this->setAspect( width / height );
    }

    void Camera::setAspect(float aspect) {
        __updateProj = true;
        __params.aspect = aspect;
    }

    void Camera::setPosition(const glm::vec4& pos) {
        __updateView = true;
        __position = pos;
    }

    void Camera::setFOV(float fov) {
        __updateProj = true;
        __params.fov = fov;
        CLIP_BETWEEN( __params.fov, FOV_MIN, FOV_MAX );
    }

    void Camera::setYaw(float YawDeg) {
        this->rotateY( YawDeg - __rotation.yaw );
    }

    void Camera::setPitch(float PitchDeg) {
        this->rotateX( PitchDeg - __rotation.pitch );
    }

    void Camera::changeFOV(float deltaFovDeg) {
        __updateProj = true;
        __params.fov += deltaFovDeg;
        CLIP_BETWEEN( __params.fov, FOV_MIN, FOV_MAX );
    }

    void Camera::moveX(float dist) {
        __updateView = true;
        __position.x += dist;
    }

    void Camera::moveY(float dist) {
        __updateView = true;
        __position.y += dist;
    }

    void Camera::moveZ(float dist) {
        __updateView = true;
        __position.z += dist;
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

    const glm::mat4& Camera::projXview() const {
        if ( !__updateProj && !__updateView ) return __m_ProjViewCache;
        if ( __updateProj ) this->updateProjMatrix();
        if ( __updateView ) this->updateViewMatrix();
        __m_ProjViewCache = __m_projection * __m_view;
        return __m_ProjViewCache;
    }
}
