#ifndef PGR_SEM_COPAKOND_CAMERA_H
#define PGR_SEM_COPAKOND_CAMERA_H

#include "../pgr-portable.h"
#include "geometry.h"
#include "../light/fog.h"

#define FRONT 0
#define BACK 1
#define LEFT 2
#define RIGHT 3
#define UP 4
#define DOWN 5

#define MAX_FOV 359.0f
#define MIN_FOV 1.0f

namespace copakond {
    class Camera : Geometry {
    private:
        const glm::vec3 _worldUp = glm::vec3(0.0f, 1.0f, 0.0f);

        glm::vec3 _front;
        glm::vec3 _up;
        glm::vec3 _right;

        float _movementSpeed;
        float _mouseSensitivity;
        float _maxPitch;

        float _nearZ;
        float _farZ;
        float _fov; // fovY

        Fog _fog = Fog();

        void updateCameraVectors(); // calculates front, up based off of yaw and pitch and position

    public:
        Camera(const glm::vec3 &startPosition, const glm::vec3 &startLookPoint, float distance);

        void lookToPoint(const glm::vec3 &point);
        void setRotation(const glm::vec3& rotation) override;
        void setRotationDegrees(const glm::vec3& rotationDegrees) override;
        void addFov(float fov);

        glm::mat4 getViewMatrix();
        glm::mat4 getProjectionMatrix(float aspectWidth, float aspectHeight);

        glm::vec3 getPosition() { return _position; }

        glm::vec3& position() { return _position; }
        glm::vec3& rotation() { return _rotation; }

        void processKeyboard(int direction, float deltaTime);
        void processMouseMovement(float deltaX, float deltaY);
        void processMouseDrag(float deltaX, float deltaY);

        void setFog(const Fog &fog) { _fog = fog; }
        Fog getFog() const { return _fog; }
    };
}
#endif //PGR_SEM_COPAKOND_CAMERA_H
