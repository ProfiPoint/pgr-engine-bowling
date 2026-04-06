#include "camera.h"

namespace copakond {
    Camera::Camera(const glm::vec3 &startPosition, const glm::vec3 &startLookPoint, float distance) {
        position = startPosition;
        lookToPoint(startLookPoint); // startLookPoint is default (0,0,0)

        fov = 45.0f;
        nearZ = 0.1f;
        farZ = distance;
        maxPitch = 89.0f;
        movementSpeed = 2.0f;
        mouseSensitivity = 0.1f;

        updateCameraVectors();
    }

    void Camera::updateCameraVectors() {
        float yaw_rad = glm::radians(yaw);
        float pitch_rad = glm::radians(pitch);

        // update yaw pitch, (+90 pitch should be up, -90 down) from: https://learnopengl.com/Getting-started/Camera
        front = glm::vec3(
            cos(yaw_rad) * cos(pitch_rad),
            sin(pitch_rad),
            sin(yaw_rad) * cos(pitch_rad)
        );

        front = glm::normalize(front);
        right = glm::normalize(glm::cross(front, worldUp)); // (0,0,-1) x (0,1,0) = (1,0,0)
        up = glm::normalize(glm::cross(right, front));
    }

    // sets yaw and pitch based off of position and look point
    glm::vec3 Camera::lookToPoint(const glm::vec3 &point) { // https://learnopengl.com/Getting-started/Camera
        glm::vec3 direction = glm::normalize(point - position);

        pitch = glm::degrees(asin(direction.y));
        yaw = glm::degrees(atan2(direction.z, direction.x));

        return direction;
    }

    glm::mat4 Camera::getViewMatrix() {
        return glm::lookAt(position, position + front, up);
    }

    glm::mat4 Camera::getProjectionMatrix(float WIN_WIDTH, float WIN_HEIGHT) {
        float aspect = WIN_WIDTH / WIN_HEIGHT;
        return glm::perspective(glm::radians(fov), aspect, nearZ, farZ);
    }

    void Camera::processKeyboard(int direction, float deltaTime) {
        glm::vec3 frontNorm = glm::normalize(glm::vec3(front.x, 0.0f, front.z)); // takes look vector, ignores y and norm.

        switch (direction) {
            case FRONT:
                position += frontNorm * movementSpeed * deltaTime;
                break;
            case BACK:
                position -= frontNorm * movementSpeed * deltaTime;
                break;
            case LEFT:
                position -= right * movementSpeed * deltaTime;
                break;
            case RIGHT:
                position += right * movementSpeed * deltaTime;
                break;
        }
    }

    void Camera::processMouseMovement(float deltaX, float deltaY) {
        yaw += deltaX * mouseSensitivity;
        pitch += deltaY * mouseSensitivity;
        yaw = fmod(yaw, 360.0f);
        pitch = glm::clamp(pitch, -maxPitch, maxPitch);
        updateCameraVectors();
    }
}