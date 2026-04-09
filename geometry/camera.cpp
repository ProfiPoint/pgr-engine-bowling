#include "camera.h"

namespace copakond {
    Camera::Camera(const glm::vec3 &startPosition, const glm::vec3 &startLookPoint, float distance) {
        _position = startPosition;
        _farZ = distance;
        _nearZ = 0.1f;
        _fov = 45.0f;
        _maxPitch = 89.0f;
        _movementSpeed = 2.0f;
        _mouseSensitivity = 0.1f;

        lookToPoint(startLookPoint); // startLookPoint is default (0,0,0)
        updateCameraVectors();
    }

    void Camera::updateCameraVectors() {
        float yawRad = glm::radians(_yaw);
        float pitchRad = glm::radians(_pitch);

        // update yaw pitch, (+90 pitch should be up, -90 down) from: https://learnopengl.com/Getting-started/Camera
        _front = glm::vec3(
            cos(yawRad) * cos(pitchRad),
            sin(pitchRad),
            sin(yawRad) * cos(pitchRad)
        );

        _front = glm::normalize(_front);
        _right = glm::normalize(glm::cross(_front, _worldUp)); // (0,0,-1) x (0,1,0) = (1,0,0)
        _up = glm::normalize(glm::cross(_right, _front));
    }

    // sets yaw and pitch based off of position and look point
    void Camera::lookToPoint(const glm::vec3 &point) {
        // https://learnopengl.com/Getting-started/Camera
        glm::vec3 direction = glm::normalize(point - _position);

        _pitch = glm::degrees(asin(direction.y));
        _yaw = glm::degrees(atan2(direction.z, direction.x));
    }

    glm::mat4 Camera::getViewMatrix() {
        return glm::lookAt(_position, _position + _front, _up);
    }

    glm::mat4 Camera::getProjectionMatrix(float winWidth, float winHeight) {
        float aspect = winWidth / winHeight;
        return glm::perspective(glm::radians(_fov), aspect, _nearZ, _farZ);
    }

    void Camera::processKeyboard(int direction, float deltaTime) {
        glm::vec3 frontNorm = glm::normalize(glm::vec3(_front.x, 0.0f, _front.z)); // takes look vector, ignores y and norm.

        switch (direction) {
            case FRONT:
                _position += frontNorm * _movementSpeed * deltaTime;
                break;
            case BACK:
                _position -= frontNorm * _movementSpeed * deltaTime;
                break;
            case LEFT:
                _position -= _right * _movementSpeed * deltaTime;
                break;
            case RIGHT:
                _position += _right * _movementSpeed * deltaTime;
                break;
        }
    }

    void Camera::processMouseMovement(float deltaX, float deltaY) {
        _yaw += deltaX * _mouseSensitivity;
        _pitch += deltaY * _mouseSensitivity;
        _yaw = fmod(_yaw, 360.0f);
        _pitch = glm::clamp(_pitch, -_maxPitch, _maxPitch);
        updateCameraVectors();
    }
}
