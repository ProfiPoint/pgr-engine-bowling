#include "rigidSphere.h"

namespace copakond {
    RigidSphere::RigidSphere(const glm::vec3 &position, const glm::vec3 &rotation, const glm::vec3 &scale, bool debug) :
    CollisionSphere(position, rotation, scale, debug) {
        if (debug) {
            _material = std::make_shared<Material>();
            _material->ambient() = glm::vec3(1.0f, 0.6f, 0.0f);
            _material->diffuse() = glm::vec3(1.0f, 0.6f, 0.0f);
            _material->specular() = glm::vec3(0.0f, 0.0f, 0.0f);
            _material->alpha() = 0.25f;
        }
    }

    void RigidSphere::physics_process(float deltaTime, const std::vector<CollisionShape*>& allColliders) {
        glm::vec3 prevPosition = position();
        position() += _velocity * deltaTime; // update pos

        bool collides = false; // check collisions
        for (CollisionShape* collider : allColliders) {
            if (collider != this && collider->isEnabled()) {
                if (collider->collisionCheck(*this)) {
                    collides = true;
                    break;
                }
            }
        }

        if (collides) { // if collides restore prev position
            position() = prevPosition;
            _velocity.y = 0.0f;
        }
    }
}