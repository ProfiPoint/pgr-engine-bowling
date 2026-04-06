#ifndef PGR_SEM_COPAKOND_CAMERA_H
#define PGR_SEM_COPAKOND_CAMERA_H

#include "pgr.h"

#define FRONT 0
#define BACK 1
#define LEFT 2
#define RIGHT 3

namespace copakond {
    class Camera {
    private:
        glm::vec3 position;
        glm::vec3 front;
        glm::vec3 up;
        glm::vec3 right;
        glm::vec3 worldUp;

        float movementSpeed;
        float mouseSensitivity;
        float maxPitch;

        float nearZ;
        float farZ;

        float fov; // fovY
        float yaw;
        float pitch;

        void updateCameraVectors(); // calculates front, up based off of yaw and pitch and position

    public:
        Camera(const glm::vec3 &startPosition, const glm::vec3 &startLookVectorm, float distance);

        glm::mat4 getViewMatrix();
        glm::mat4 getProjectionMatrix(float aspectWidth, float aspectHeight);

        void processKeyboard(int direction, float deltaTime);
        void processMouseMovement(float deltaX, float deltaY);
    };
}

#endif //PGR_SEM_COPAKOND_CAMERA_H