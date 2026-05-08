#include "rigidBody.h"

namespace copakond {
    RigidBody::RigidBody(const glm::vec3 &position, const glm::vec3 &rotation, const glm::vec3 &scale, bool debug) :
    CollisionBox(position, rotation, scale, debug) {
        if (debug) {
            _material = std::make_shared<Material>();
            _material->ambient() = glm::vec3(1.0f, 0.6f, 0.0f);
            _material->diffuse() = glm::vec3(1.0f, 0.6f, 0.0f);
            _material->specular() = glm::vec3(0.0f, 0.0f, 0.0f);
            _material->alpha() = 0.25f;
        }
    }

    void RigidBody::physics_process(float deltaTime, const std::vector<CollisionShape*>& allColliders) {
        // implementation of delta fix t

        float deltaTimeLeft = deltaTime;
        while (deltaTimeLeft > 0.0f) {
            float timeDeltaNow = DELTA_TIME_FIXED;
            if (deltaTimeLeft < DELTA_TIME_FIXED) { timeDeltaNow = deltaTimeLeft; }
            deltaTimeLeft -= DELTA_TIME_FIXED;

            _velocity += _gravity * timeDeltaNow; // gravity
            _velocity *= (1.0f - (_airFriction * timeDeltaNow)); // air friction formula

            // do the position updates for each axe individually
            for (int i = 0; i < 3; ++i) {
                float prevPosition = position()[i];
                position()[i] += _velocity[i] * timeDeltaNow; // update pos

                glm::vec3 curAxeVelocity(0.0f);
                curAxeVelocity[i] = _velocity[i];

                CollisionResult result = collisionFalse();
                CollisionShape* resCollider = nullptr;
                for (CollisionShape* collider : allColliders) {
                    if (collider != this && collider->isEnabled()) {
                        result = collider->collisionCheckDetailed(*this, curAxeVelocity, true);
                        if (result.collides) {
                            resCollider = collider;
                            break;
                        }
                    }
                }

                if (result.collides) { // if collides restore prev position
                    position()[i] = prevPosition;

                    float bouncinessRes = this->physicsMaterial.bounciness * resCollider->physicsMaterial.bounciness;
                    float frictionRes = this->physicsMaterial.friction * resCollider->physicsMaterial.friction;

                    glm::vec3 normalDirVel = glm::dot(result.normal, _velocity) * result.normal; // reflect angle norm corr
                    _velocity = normalDirVel * (-bouncinessRes) + (_velocity - normalDirVel) * (1.0f - frictionRes); // apply bounciness and friction formula

                    if (glm::length(_velocity) < 0.001f) { // oscilation prevention
                        _velocity = glm::vec3(0.0f);
                    }
                }
            }
        }
    }
}