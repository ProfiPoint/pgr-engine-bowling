#include "camera.h"

namespace copakond {
    Camera::Camera(const glm::vec3 &startPosition, const glm::vec3 &startLookPoint, float distance) {
        _translation = startPosition;
        _farZ = distance;
        _nearZ = 0.1f;
        _fov = 45.0f;
        _maxPitch = 89.0f;
        _movementSpeed = 2.0f;
        _mouseSensitivity = 0.1f;

        lookToPoint(startLookPoint); // startLookPoint is default (0,0,0)
        updateCameraVectors();
    }

    void Camera::setRotation(const glm::vec3& rotation) {
        Geometry::setRotation(rotation);
        updateCameraVectors();
    }

    void Camera::setRotationDegrees(const glm::vec3& rotationDegrees) {
        Geometry::setRotationDegrees(rotationDegrees);
        updateCameraVectors();
    }

    void Camera::updateCameraVectors() {
        //https://learnopengl.com/Getting-started/Camera
        _front = glm::vec3(
            cos(_rotation.y) * cos(_rotation.x),
            sin(_rotation.x),
            sin(_rotation.y) * cos(_rotation.x)
        );

        _front = glm::normalize(_front);
        _right = glm::normalize(glm::cross(_front, _worldUp)); // (0,0,-1) x (0,1,0) = (1,0,0)
        _up = glm::normalize(glm::cross(_right, _front));
    }

    // sets yaw and pitch based off of position and look point
    void Camera::lookToPoint(const glm::vec3 &point) {
        // https://learnopengl.com/Getting-started/Camera
        _front = glm::normalize(point - _translation);

        float pitch = glm::degrees(asin(_front.y));
        float yaw = glm::degrees(atan2(_front.z, _front.x));

        setRotationDegrees(glm::vec3(pitch, yaw, 0.0f));
    }

    glm::mat4 Camera::getViewMatrix() {
        return glm::lookAt(_translation, _translation + _front, _up);
    }

    glm::mat4 Camera::getProjectionMatrix(float winWidth, float winHeight) {
        float aspect = winWidth / winHeight;
        return glm::perspective(glm::radians(_fov), aspect, _nearZ, _farZ);
    }

    void Camera::processKeyboard(int direction, float deltaTime) {
        glm::vec3 frontNorm = glm::normalize(glm::vec3(_front.x, 0.0f, _front.z)); // takes look vector, ignores y and norm.

        switch (direction) {
            case FRONT:
                _translation += frontNorm * _movementSpeed * deltaTime;
                break;
            case BACK:
                _translation -= frontNorm * _movementSpeed * deltaTime;
                break;
            case LEFT:
                _translation -= _right * _movementSpeed * deltaTime;
                break;
            case RIGHT:
                _translation += _right * _movementSpeed * deltaTime;
                break;
            case UP:
                _translation += _worldUp * _movementSpeed * deltaTime;
                break;
            case DOWN:
                _translation -= _worldUp * _movementSpeed * deltaTime;
        }
    }

    void Camera::addFov(float fovOffset) {
        _fov += fovOffset;
        _fov = glm::clamp(_fov, MIN_FOV, MAX_FOV);
    }

    void Camera::processMouseMovement(float deltaX, float deltaY) {
        glm::vec3 currentRotDeg = getRotationDegrees();

        currentRotDeg.y += deltaX * _mouseSensitivity; // Yaw
        currentRotDeg.x += deltaY * _mouseSensitivity; // Pitch

        currentRotDeg.y = fmod(currentRotDeg.y, 360.0f);

        if (currentRotDeg.x > _maxPitch) currentRotDeg.x = _maxPitch;
        if (currentRotDeg.x < -_maxPitch) currentRotDeg.x = -_maxPitch;

        setRotationDegrees(currentRotDeg);
    }

    void Camera::processMouseDrag(float deltaX, float deltaY) {
        float velocityX = deltaX * _mouseSensitivity;
        float velocityY = deltaY * _mouseSensitivity;
        _translation += _right * velocityX;
        _translation += _up * velocityY;
    }
}
