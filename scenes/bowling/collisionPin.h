#ifndef PGR_SEM_COPAKOND_COLLISIONPIN_H
#define PGR_SEM_COPAKOND_COLLISIONPIN_H

#include "../../meshes/collision/collisionSphere.h"
#include "../../meshes/collision/rigidSphere.h"

namespace copakond {
    enum class PinState { IDLE, FALLING, DEAD };

    /** @brief Specialized sphere collider for bowling pins with custom fall physics */
    class CollisionPin : public CollisionSphere {
    private:
        PinState _state = PinState::IDLE;
        glm::vec3 _startPosition;
        glm::vec3 _fallAxis;
        float _fallAngle = 0.0f;
        float _timeSinceHit = 0.0f;

    public:
        CollisionPin(const glm::vec3 &position, const glm::vec3 &rotation, const glm::vec3 &scale, bool visible = true);

        /** @brief Custom physics update simulating toppling over when hit */
        void updatePin(float deltaTime, RigidSphere* ball);

        CollisionResult collisionCheckDetailed(const CollisionShape &mesh, glm::vec3 velocity, bool calculateNormal) override;

        /** @brief Restores pin to its initial standing position and state */
        void reset();
        bool isDown() { return _state == PinState::DEAD; }
    };
}

#endif //PGR_SEM_COPAKOND_COLLISIONPIN_H
