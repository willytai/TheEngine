#ifndef __CAMERA_H__
#define __CAMERA_H__

#ifndef GLM_FORCE_SWIZZLE
#define GLM_FORCE_SWIZZLE
#endif

#include "core/core.h"
#include "glm/glm.hpp"

namespace Engine7414
{
    struct Rotation
    {
        float pitch;
        float yaw;
    };

    // this is a camera for 3D rendering (perspective projection)
    class Camera
    {
    public:
        Camera(float FovDeg, float aspect, float nearClip = 0.1f, float farClip = 100.0f);
        ~Camera();

        void setPosition(const glm::vec4& pos);
        void setFOV(float deltaFovDeg);
        void setYaw(float deltaYawDeg);
        void setPitch(float deltaPitchDeg);
        void setAspect(float aspect);
        void setAspect(float width, float height);

        inline const Rotation&  rotation() const { return __rotation; }
        inline const glm::vec4& position() const { return __position; }
        inline const glm::mat4& projection() const { return __m_projection; }
        inline const glm::mat4& view() const { return __m_view; }
        inline const glm::mat4& projXview() const {
            if ( __updateProjViewCache ) __m_ProjViewCache = __m_projection*__m_view;
            return __m_ProjViewCache;
        }

    private:
        void updateViewMatrix();
        void updateProjMatrix();

    private:
        glm::mat4   __m_projection;
        glm::mat4   __m_view;
        glm::vec4   __position;
        glm::vec4   __front;
        Rotation    __rotation;

        // simply a cache for further optimization
        bool                __updateProjViewCache;
        mutable glm::mat4   __m_ProjViewCache;

        // cache of the camera's parameters
        // access won't be granted outside of this class
        struct {
            float fov;
            float aspect;
            float nearClip;
            float farClip;
        } __params;
    };
}

#endif /* __CAMERA_H__ */
