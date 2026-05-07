#ifndef PGR_SEM_COPAKOND_RIGIDSPHERE_H
#define PGR_SEM_COPAKOND_RIGIDSPHERE_H
#include "collisionSphere.h"

namespace copakond {
    class RigidSphere : public CollisionSphere {
    private:
        glm::vec3 _velocity = glm::vec3(0.0f, 0.0f, 0.0f);
        glm::vec3 _gravity = glm::vec3(0.0f, -9.81f, 0.0f); // Earth gravity
        float _airFriction = 0.1f;

    public:
        RigidSphere(const glm::vec3 &position = glm::vec3(0.0f), const glm::vec3 &rotation = glm::vec3(0.0f),
            const glm::vec3 &scale = glm::vec3(1.0f), bool debug = false);

        void physics_process(float deltaTime, const std::vector<CollisionShape*>& allColliders);
        glm::vec3& velocity() { return _velocity; }
        glm::vec3& gravity() { return _gravity; }
        void setAirFriction(float airFriction);
        float getAirFriction() const { return _airFriction; }
    };
}

#endif //PGR_SEM_COPAKOND_RIGIDSPHERE_H
