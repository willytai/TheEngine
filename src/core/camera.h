#ifndef __CAMERA_H__
#define __CAMERA_H__

#define GLM_FORCE_SWIZZLE

#include "GLmacro.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include <GLFW/glfw3.h>
#include <functional>

class Camera
{
    static glm::vec3 cameraUp; // (+y axis)
    static float     FOV;      // field of focus
    static float     wWidth;   // window width
    static float     wHeight;  // window height
public:
    Camera(GLFWwindow* window);
    ~Camera();

    void onUpdate(const float& deltaTime);

    void setSensitivity(float sensitivity) { _sensitivity = sensitivity; }
    void setMovementSpeed(float movementSpeed) { _movement_speed = movementSpeed; }

    inline float* getSensitivityPtr() { return &_sensitivity; }
    inline float* getMovementSpeedPtr() { return &_movement_speed; }

    inline const glm::mat4& getView() const { return _view; }
    inline const glm::mat4& getPerspective() const { return _perspective; }

private:
    void moveZ(const float& deltaTime);
    void moveX(const float& deltaTime);
    void updateEuler(const float& deltaTime);
    void updateMatrices();

private:
    static void scrollCallback(GLFWwindow* window, double xoffset, double yoffset);
    static void windowResizeCallback( GLFWwindow* window, int width, int height);

private:
    GLFWwindow* _window;
    float       _sensitivity;
    float       _movement_speed;
    float       _pitch;
    float       _yaw;
    float       _roll;
    float       _cursorX;
    float       _cursorY;
    bool        _pressed;
    glm::vec3   _pos;
    glm::vec3   _front;
    glm::mat4   _view;
    glm::mat4   _perspective;
};

#endif /* __CAMERA_H__ */
