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
        // implementation of delta fix t
        float deltaTimeLeft = deltaTime;
        while (deltaTimeLeft > 0.0f) {
            float timeDeltaNow = DELTA_TIME_FIXED;
            if (deltaTimeLeft < DELTA_TIME_FIXED) { timeDeltaNow = deltaTimeLeft; }
            deltaTimeLeft -= DELTA_TIME_FIXED;

            _velocity += _gravity * timeDeltaNow; // gravity
            _velocity *= (1.0f - (_airFriction * timeDeltaNow)); // air friction formula

            glm::vec3 prevPosition = position();
            position() += _velocity * timeDeltaNow; // update pos

            CollisionResult result = collisionFalse();
            for (CollisionShape* collider : allColliders) {
                if (collider != this && collider->isEnabled()) {
                    result = collider->collisionCheckDetailed(*this, _velocity, true);
                    if (result.collides) {
                        break;
                    }
                }
            }

            if (result.collides) { // if collides restore prev position
                position() = prevPosition;
                _velocity = result.reflection;
            }
        }
    }
}