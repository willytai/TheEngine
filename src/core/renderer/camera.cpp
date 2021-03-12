#include "core/renderer/camera.h"
#include "glm/gtc/matrix_transform.hpp"

namespace Engine7414
{
    Camera::Camera(float FovDeg, float aspect, float nearClip, float farClip)
        : __m_projection(glm::mat4(1.0f)),
          __m_view(glm::mat4(1.0f)),
          __position(0.0f, 0.0f, 0.0f, 1.0f),
          __front(0.0f, 0.0f, 1.0f, 0.0f),
          __rotation({ 0.0f, 0.0f }),
          __updateProjViewCache(false),
          __m_ProjViewCache(glm::mat4(1.0f)),
          __params({ FovDeg, aspect, nearClip, farClip })
    {
        __m_projection = glm::perspective( glm::radians(FovDeg),
                                           aspect, nearClip, farClip );
        __m_ProjViewCache = __m_projection*__m_view;
    }

    Camera::~Camera() {

    }

    void Camera::setAspect(float width, float height) {
        this->setAspect( width / height );
    }

    void Camera::setAspect(float aspect) {
        __updateProjViewCache = true;
        __params.aspect = aspect;
        this->updateProjMatrix();
    }

    void Camera::setPosition(const glm::vec4& pos) {
        __updateProjViewCache = true;
        __position = pos;
        this->updateViewMatrix();
    }

    void Camera::setFOV(float deltaFovDeg) {
        __updateProjViewCache = true;
        __params.fov += deltaFovDeg;
        this->updateProjMatrix();
    }

    void Camera::setYaw(float deltaYawDeg) {
        __updateProjViewCache = true;
        __rotation.yaw += deltaYawDeg;
        __front = glm::rotate( glm::mat4(1.0f), glm::radians(deltaYawDeg), glm::vec3(0.0f, 1.0f, 0.0f) )*__front;
        this->updateViewMatrix();
    }

    void Camera::setPitch(float deltaPitchDeg) {
        __updateProjViewCache = true;
        __rotation.pitch += deltaPitchDeg;
        __front = glm::rotate( glm::mat4(1.0f), glm::radians(deltaPitchDeg), glm::vec3(1.0f, 0.0f, 0.0f) )*__front;
        this->updateViewMatrix();
    }

    void Camera::updateViewMatrix() {
        __m_view = glm::lookAt( __position.xyz(),
                                (__position+__front).xyz(),
                                glm::vec3(0.0f, 1.0f, 0.0f) );
    }

    void Camera::updateProjMatrix() {
        __m_projection = glm::perspective( glm::radians(__params.fov),
                                           __params.aspect,
                                           __params.nearClip,
                                           __params.farClip );
    }
}
