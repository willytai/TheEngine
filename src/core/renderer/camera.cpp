#include "core/renderer/camera.h"
#include "core/renderer/renderer.h"
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

    void CameraBase::zoom(const float& level) {
        CORE_ASSERT(false, "not implemented");
    }

    void CameraBase::setAspectRatio(const float& aspect) {
        __updateProj = true;
        params.aspect = aspect;
    }

    const glm::mat4& CameraBase::projection() const {
        if (__updateProj) {
            this->updateProjMatrix();
        }
        return __m_projection;
    }

    /**************************************/
    /* 3D Camera (Perspective Projection) */
    /**************************************/
    Scoped<Camera> Camera::create(float fov, float aspect, float nearClip, float farClip) {
        fov = fov > 0.0f ? fov : 45.0f;
        nearClip = nearClip > 0.0f ? nearClip : 1.0f;
        farClip = farClip > 1.0f ? farClip : 1000.0f;
        return CreateScoped<Camera>(fov, aspect, nearClip, farClip);
    }

    Camera::Camera(float fov, float aspect, float nearClip, float farClip) {
        params = { fov, aspect, nearClip, farClip };
    }

    void Camera::zoom(const float& fov) {
        __updateProj = true;
        params.fov = fov;
        CLIP_BETWEEN( params.fov, CameraBase::FOV_MIN, CameraBase::FOV_MAX );
    }

    void Camera::updateProjMatrix() const {
        __m_projection = glm::perspective( glm::radians(params.fov),
                                           params.aspect,
                                           params.nearClip,
                                           params.farClip );
        // TODO uncomment this
        Renderer::setUpdateMatFlag();
        Renderer2D::setUpdateMatFlag();
        __updateProj = false;
    }

    /***************************************/
    /* 2D Camera (Orthographic Projection) */
    /***************************************/
    Scoped<Camera2D> Camera2D::create(float size, float aspect, float nearClip, float farClip) {
        size = size > 0.0f ? size : 1.0f;
        return CreateScoped<Camera2D>(size, aspect, nearClip, farClip);
    }

    Camera2D::Camera2D(float size, float aspect, float nearClip, float farClip) {
          params = { size, aspect, nearClip, farClip };
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
