#include "camera.h"

namespace copakond {
    //TODO implement startLookVector to pitch, yaw
    Camera::Camera(const glm::vec3 &startPosition, const glm::vec3 &startLookVector, float distance) {
        position = startPosition;
        worldUp = glm::vec3(0.0f, 1.0f, 0.0f); //should use startLookVector
        right = glm::normalize(cross(startLookVector, worldUp)); // (0,0,-1) x (0,1,0) = (1,0,0)

        yaw = 0.0f; // should use startLookVector
        pitch = 0.0f; //should use startLookVector

        fov = 45.0f;
        nearZ = 0.1f;
        farZ = distance;
        maxPitch = 89.0f;
        movementSpeed = 2.0f;
        mouseSensitivity = 0.1f;
    }

    void Camera::updateCameraVectors() {
        float yaw_rad = glm::radians(yaw);
        float pitch_rad = glm::radians(pitch);

        // update yaw pitch, (+90 pitch should be up, -90 down)
        front = glm::vec3(
        cos(yaw_rad) * sin(pitch_rad),
        sin(pitch_rad),
        cos(pitch_rad) * sin(yaw_rad)
        );

        front = glm::normalize(front);
        right = glm::normalize(glm::cross(front, worldUp));
        up = glm::normalize(glm::cross(right, front));
    }

    glm::mat4 Camera::getViewMatrix() {
        return glm::lookAt(position, position + front, up);
    }

    glm::mat4 Camera::getProjectionMatrix(float WIN_WIDTH, float WIN_HEIGHT) {
        updateCameraVectors();
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
    }
}