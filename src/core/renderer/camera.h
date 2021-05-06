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

    union CameraParam
    {
        struct { float fov;  float aspect; float nearClip; float farClip; };
        struct { float size; float aspect; float nearClip; float farClip; };
    };

    class CameraBase
    {
        friend class HierarchyPanel;
    public:
        enum class Type {
            Orthographic,
            Perspective
        };
    public:
        static float FOV_MIN;
        static float FOV_MAX;
    public:
        CameraBase();
        virtual ~CameraBase() = default;

        virtual const char* projection_str() const = 0;

        virtual void setAspectRatio(const float& aspect) = 0;
        virtual void zoom(const float& level) = 0;

        const glm::mat4& projection() const;

    private:
        virtual void updateProjMatrix() const = 0;

    protected:
        // TODO: mutable?
        // simply a cache for further optimization
        // these matrices are guaranteed to be re-calculated at most once in each frame
        mutable bool        __updateProj;
        mutable glm::mat4   __m_projection;

        // cache of the camera's parameters
        // access won't be granted outside of this class
        // except for the HierarchyPanel (friended)
        CameraParam params;
    };

    // this is a camera for 3D rendering (perspective projection)
    class Camera : public CameraBase
    {
    public:
        Camera(float FovDeg, float aspect, float nearClip = 0.1f, float farClip = 100.0f);
        ~Camera() = default;

        const char* projection_str() const override { return "Perspective"; }

        // void setPosition(const glm::vec4& pos) override;
        // void setPosition(const glm::vec3& pos) override;
        void setAspectRatio(const float& asepct) override;

        void setFOV(float fov);
        void setYaw(float YawDeg);
        void setPitch(float PitchDeg);

        void zoom(const float& fov) override;
        // void rotateY(float deltaYawDeg);
        // void rotateX(float deltaPitchDeg);

        inline const Rotation&  rotation() const { return __rotation; }

    private:
        void updateProjMatrix() const override;

    private:
        glm::vec4   __front;
        Rotation    __rotation;
    };
    typedef Camera Camera3D;

    class Camera2D : public CameraBase
    {
    public:
        Camera2D(float size, float aspect, float nearClip = -1.0f, float farClip = 1.0f);
        ~Camera2D() = default;

        const char* projection_str() const override { return "Orthographic"; }
        void setAspectRatio(const float& aspect) override;
        void zoom(const float& level) override;

        static Scoped<Camera2D> create(float size, float aspect, float nearClip, float farClip);
    private:
        void updateProjMatrix() const override;

    private:
        float       __rotation;
    };
}

#endif /* __CAMERA_H__ */
