#ifndef PGR_SEM_COPAKOND_RIGIDBODY_H
#define PGR_SEM_COPAKOND_RIGIDBODY_H
#include "collisionBox.h"

namespace copakond {
    /** @brief Kinematic object affected by gravity, friction, and collision resolution */
    class RigidBody : public CollisionBox {
    private:
        glm::vec3 _velocity = glm::vec3(0.0f, 0.0f, 0.0f);
        glm::vec3 _gravity = glm::vec3(0.0f, -9.81f, 0.0f); // Earth gravity
        float _airFriction = 0.1f;
        bool _isOnFloor = false;

    public:
        RigidBody(const glm::vec3 &position = glm::vec3(0.0f), const glm::vec3 &rotation = glm::vec3(0.0f),
            const glm::vec3 &scale = glm::vec3(1.0f), bool debug = false);

        /**
         * @brief Integrates velocity/gravity and resolves collisions iteratively across axes.
         * @param deltaTime Variable time step.
         * @param allColliders List of potential obstacles in the scene.
         */
        void physics_process(float deltaTime, const std::vector<CollisionShape*>& allColliders);
        glm::vec3& velocity() { return _velocity; }
        glm::vec3& gravity() { return _gravity; }
        void setAirFriction(float airFriction);
        float getAirFriction() const { return _airFriction; }

        bool isOnFloor() const { return _isOnFloor; }
    };
}

#endif //PGR_SEM_COPAKOND_RIGIDBODY_H
