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
        const glm::vec3 _worldUp = glm::vec3(0.0f, 1.0f, 0.0f);

        glm::vec3 _position;
        glm::vec3 _front;
        glm::vec3 _up;
        glm::vec3 _right;

        float _movementSpeed;
        float _mouseSensitivity;
        float _maxPitch;

        float _nearZ;
        float _farZ;

        float _fov; // fovY
        float _yaw;
        float _pitch;

        void updateCameraVectors(); // calculates front, up based off of yaw and pitch and position

    public:
        Camera(const glm::vec3 &startPosition, const glm::vec3 &startLookPoint, float distance);

        void lookToPoint(const glm::vec3 &point);

        glm::mat4 getViewMatrix();
        glm::mat4 getProjectionMatrix(float aspectWidth, float aspectHeight);

        void processKeyboard(int direction, float deltaTime);
        void processMouseMovement(float deltaX, float deltaY);
    };
}
#endif //PGR_SEM_COPAKOND_CAMERA_H
