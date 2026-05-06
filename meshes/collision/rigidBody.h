#ifndef PGR_SEM_COPAKOND_RIGIDBODY_H
#define PGR_SEM_COPAKOND_RIGIDBODY_H
#include "collisionBox.h"

namespace copakond {
    class RigidBody : public CollisionBox {
    private:
        glm::vec3 _velocity = glm::vec3(0.0f, 0.0f, 0.0f);

    public:
        RigidBody(const glm::vec3 &position = glm::vec3(0.0f), const glm::vec3 &rotation = glm::vec3(0.0f),
            const glm::vec3 &scale = glm::vec3(1.0f), bool debug = false);

        void physics_process(float deltaTime, const std::vector<CollisionShape*>& allColliders);
        glm::vec3& velocity() { return _velocity; }
    };
}

#endif //PGR_SEM_COPAKOND_RIGIDBODY_H
