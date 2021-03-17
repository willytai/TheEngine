#ifndef __CAMERA_H__
#define __CAMERA_H__

#ifndef GLM_FORCE_SWIZZLE
#define GLM_FORCE_SWIZZLE
#endif

#include "core/core.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

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
        static float FOV_MIN;
        static float FOV_MAX;
    public:
        Camera(float FovDeg, float aspect, float nearClip = 0.1f, float farClip = 100.0f);
        ~Camera();

        void setPosition(const glm::vec4& pos);
        void setFOV(float fov);
        void setAspect(float aspect);
        void setAspect(float width, float height);
        void setYaw(float YawDeg);
        void setPitch(float PitchDeg);

        void changeFOV(float deltaFovDeg);
        void moveX(float dist);
        void moveY(float dist);
        void moveZ(float dist);
        void rotateY(float deltaYawDeg);
        void rotateX(float deltaPitchDeg);

        inline const Rotation&  rotation() const { return __rotation; }
        inline const glm::vec4& position() const { return __position; }
        inline const glm::mat4& projection() const { return __m_projection; }
        inline const glm::mat4& view() const { return __m_view; }

        // the stuff that the renderer needs
        const glm::mat4& projXview() const;

    private:
        void updateViewMatrix() const;
        void updateProjMatrix() const;

    private:
        glm::vec4   __position;
        glm::vec4   __front;
        Rotation    __rotation;

        // simply a cache for further optimization
        // these matrices are guaranteed to re-calculated at most once in each frame
        mutable bool        __updateProj;
        mutable bool        __updateView;
        mutable glm::mat4   __m_projection;
        mutable glm::mat4   __m_view;
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
