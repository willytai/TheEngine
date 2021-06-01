#ifndef __EDITOR_CAMERA_H__
#define __EDITOR_CAMERA_H__

#include "core/renderer/camera.h"
#include "core/util/timeStep.h"
#include "core/event/event.h"

#include <utility>
#include <glm/gtx/quaternion.hpp>

namespace Engine7414
{
	class EditorCamera : public CameraBase
	{
    public:
        EditorCamera(float fov, float aspect, float nearClip = 0.1f, float farClip = 100.0f);
        ~EditorCamera() = default;
        
        void onUpdate(const TimeStep& deltaTime);
        void onEvent(Event& event);

        const glm::mat4& getViewProjection();
        const glm::mat4& getView();
        const glm::mat4& getProjection();

        inline void setViewportSize(const glm::vec2& size) { _viewportSize = size; __updateProj = true; }

        Type getType() const override { return Type::Perspective; }
        const char* projection_str() const { return "persepctive (Editor Camera)"; }

        static Scoped<EditorCamera> create();
        static Scoped<EditorCamera> create(float fov, float aspect, float nearClip, float farClip);

    private:
        void updateProjMatrix() const override;
        void updateViewMatrix();
        void updatePosition();

        bool onMouseScrolled(MouseScrolledEvent& event);

        glm::vec3 forwardDirection();
        glm::vec3 upDirection();
        glm::vec3 leftDirection();
        glm::quat orientation();

        void mouseDrag(const glm::vec2& deltaMouse);
        void mouseRotate(const glm::vec2& deltaMouse);
        void mouseZoom(const float& zoom);

        float zoomSpeed();
        std::pair<float, float> dragSpeed();

    private:
        bool        __updateView = true;

        glm::mat4   __m_view = glm::mat4(1.0f);
        glm::mat4   __m_view_proj = glm::mat4(1.0f);

        glm::vec3   _position = { 0.0f, 0.0f, 0.0f };
        glm::vec3   _focalPoint = { 0.0f, 0.0f, 0.0f };

        float       _distance = 10.0f; // distance to focal point
        float       _pitch = 0.0f;
        float       _yaw = 0.0f;

        glm::vec2   _initMousePos = { 0.0f, 0.0f };
	
        glm::vec2   _viewportSize = { 1280.0f, 960.0f };
    };
}

#endif