#include "camera.h"
#include <cmath>

glm::vec3 Camera::cameraUp = glm::vec3( 0.0f, 1.0f,  0.0f );
float     Camera::FOV      = 45.0f;
float     Camera::wWidth   = 1280.0f;
float     Camera::wHeight  = 960.0f;


Camera::Camera(GLFWwindow* window) :
    _window(window),
    _sensitivity(5.0f),
    _movement_speed(5.0f),
    _pitch(0.0f),
    _yaw(0.0f),
    _roll(0.0f),
    _cursorX(0.0f),
    _cursorY(0.0f),
    _pressed(false),
    _pos(0.0f, 2.5f, 10.0f),
    _front(0.0f, 0.0f, -1.0f) {

    // set callbacks
    glfwSetScrollCallback( _window, Camera::scrollCallback ); // scroll
    glfwSetWindowSizeCallback( _window, Camera::windowResizeCallback ); // window resize

    // initialize matrices
    this->updateMatrices();
}

Camera::~Camera() {

}

void Camera::onUpdate(const float& deltaTime) {
    // update position & roll
    if ( glfwGetKey( _window, GLFW_KEY_W ) == GLFW_PRESS ) this->moveZ( deltaTime);
    if ( glfwGetKey( _window, GLFW_KEY_S ) == GLFW_PRESS ) this->moveZ(-deltaTime);
    if ( glfwGetKey( _window, GLFW_KEY_A ) == GLFW_PRESS ) this->moveX(-deltaTime);
    if ( glfwGetKey( _window, GLFW_KEY_D ) == GLFW_PRESS ) this->moveX( deltaTime);
    if ( glfwGetKey( _window, GLFW_KEY_Q ) == GLFW_PRESS ) _roll = glm::radians( 30.0f );
    else if ( glfwGetKey( _window, GLFW_KEY_E ) == GLFW_PRESS ) _roll = glm::radians( -30.0f );
    else _roll = 0.0f;

    // update euler angles
    if ( glfwGetMouseButton( _window, GLFW_MOUSE_BUTTON_LEFT ) == GLFW_PRESS ) {
        if ( !_pressed ) { // update the starting position to the current position
            double xpos, ypos;
            glfwGetCursorPos( _window, &xpos, &ypos );
            _cursorX = (float)xpos;
            _cursorY = (float)ypos;
            _pressed = true;
        }
        else this->updateEuler( deltaTime );
    }
    else _pressed = false;

    // update matrices
    this->updateMatrices();
}

void Camera::moveZ(const float& deltaTime) {
    // always move toward the point of focus
    _pos += _movement_speed * deltaTime * _front;
}

void Camera::moveX(const float& deltaTime) {
    // cross product of the up direction and the front direction
    _pos += _movement_speed * deltaTime * glm::cross( _front, cameraUp );
}

void Camera::updateEuler(const float& deltaTime) {
    double xpos, ypos;
    glfwGetCursorPos( _window, &xpos, &ypos );
    float xoffset = (float)xpos - _cursorX;
    float yoffset = (float)ypos - _cursorY;
    _yaw   += glm::radians( xoffset * _sensitivity * deltaTime );
    _pitch += glm::radians( yoffset * _sensitivity * deltaTime );
    _cursorX = (float)xpos;
    _cursorY = (float)ypos;
}

void Camera::updateMatrices() {
    // camera direction
    _front = glm::normalize( glm::vec3(  std::cos(_pitch) * std::sin(-_yaw),
                                         std::sin(_pitch),
                                        -std::cos(_pitch) * std::cos(_yaw)
                                      )
                           );
    // view matrix
    glm::vec4 tmp = glm::rotate( glm::mat4(1.0f), _roll, _front ) * glm::vec4( cameraUp, 1.0f );
    _view = glm::lookAt( _pos,
                         _pos + _front,
                         tmp.xyz() );
    // projection matrix
    _perspective = glm::perspective( glm::radians(FOV),
                                     wWidth / wHeight,
                                     0.1f,
                                     100.0f
                                   );
}


/********************************
*           callbacks           *
********************************/
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wunused-parameter"
void Camera::scrollCallback(GLFWwindow* window, double xoffset, double yoffset) {
    FOV -= (float)yoffset;
    if ( FOV < 1.0f ) FOV = 1.0f;
    if ( FOV > 60.0f ) FOV = 60.0f;
}

void Camera::windowResizeCallback( GLFWwindow* window, int width, int height ) {
    wWidth = (float)width;
    wHeight = (float)height;
}
#pragma clang diagnostic pop
