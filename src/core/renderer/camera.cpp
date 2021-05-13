#include "core/renderer/camera.h"
#include "core/renderer/renderer2D.h"

namespace Engine7414
{
    float CameraBase::FOV_MIN = 1.0f;
    float CameraBase::FOV_MAX = 60.0f;

    /*********************/
    /* Camera Base Class */
    /*********************/
    CameraBase::CameraBase() :
        __updateProj(true),
        __m_projection(glm::mat4(1.0f))
    {}

    const glm::mat4& CameraBase::projection() const {
        if (__updateProj) {
            this->updateProjMatrix();
            Renderer2D::setUpdateMatFlag();
        }
        return __m_projection;
    }

    /**************************************/
    /* 3D Camera (Perspective Projection) */
    /**************************************/
    Camera::Camera(float FovDeg, float aspect, float nearClip, float farClip) :
        __front(0.0f, 0.0f, -1.0f, 0.0f),
        __rotation({ 0.0f, 0.0f })
    {
        params = { FovDeg, aspect, nearClip, farClip };
    }

    void Camera::setAspectRatio(const float& aspect) {
        __updateProj = true;
        params.aspect = aspect;
    }

    void Camera::setFOV(float fov) {
        __updateProj = true;
        params.fov = fov;
        CLIP_BETWEEN( params.fov, CameraBase::FOV_MIN, CameraBase::FOV_MAX );
    }

    void Camera::setYaw(float YawDeg) {
        //this->rotateY( YawDeg - __rotation.yaw );
    }

    void Camera::setPitch(float PitchDeg) {
        //this->rotateX( PitchDeg - __rotation.pitch );
    }

    void Camera::zoom(const float& fov) {
        __updateProj = true;
        params.fov = fov;
    }

    /*
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
    */

    void Camera::updateProjMatrix() const {
        __m_projection = glm::perspective( glm::radians(params.fov),
                                           params.aspect,
                                           params.nearClip,
                                           params.farClip );
        __updateProj = false;
    }

    /***************************************/
    /* 2D Camera (Orthographic Projection) */
    /***************************************/
    Scoped<Camera2D> Camera2D::create(float size, float aspect, float nearClip, float farClip) {
        size = size > 0.0f ? size : 1.0f;
        return CreateScoped<Camera2D>(size, aspect, nearClip, farClip);
    }

    Camera2D::Camera2D(float size, float aspect, float nearClip, float farClip) :
        __rotation(0.0f)
    {
          params = { size, aspect, nearClip, farClip };
    }

    void Camera2D::setAspectRatio(const float& aspect) {
        __updateProj = true;
        params.aspect = aspect;
    }

    void Camera2D::zoom(const float& level) {
        __updateProj = true;
        params.size = level;
    }

    void Camera2D::updateProjMatrix() const {
        __m_projection = glm::ortho(-params.aspect*params.size, params.aspect*params.size,
                                    -params.size, params.size,
                                     params.nearClip, params.farClip);
        Renderer2D::setUpdateMatFlag();
        __updateProj = false;
    }
}
