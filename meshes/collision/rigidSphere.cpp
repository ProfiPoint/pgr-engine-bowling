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

    void RigidSphere::rollRotation(float timeDeltaNow) {
        glm::vec3 horizontalVel = glm::vec3(_velocity.x, 0.0f, _velocity.z);
        float speed = glm::length(horizontalVel);

        if (speed > 0.001f) {
            float radius = scale().x / 2.0f; // x=y=z
            float distance = speed * timeDeltaNow;
            float angle = distance / radius; // calculate the rotation angle

            glm::vec3 axe = glm::normalize(glm::cross(glm::vec3(0.0f, 1.0f, 0.0f), horizontalVel));

            glm::quat currentRot = glm::quat(rotation());
            glm::quat deltaRot = glm::angleAxis(angle, axe); // rotation around the given axe for the given angle

            rotation() = glm::eulerAngles(deltaRot * currentRot);
        }
    }

    void RigidSphere::physics_process(float deltaTime, const std::vector<CollisionShape*>& allColliders) {
        _isOnFloor = false;
        if (!_enabled) { return; }

        float radius1 = std::max({this->scale().x, this->scale().y, this->scale().z}) * 0.866f;

        // implementation of delta fix t
        float deltaTimeLeft = deltaTime;
        while (deltaTimeLeft > 0.0f) {
            float timeDeltaNow = DELTA_TIME_FIXED;
            if (deltaTimeLeft < DELTA_TIME_FIXED) { timeDeltaNow = deltaTimeLeft; }
            deltaTimeLeft -= DELTA_TIME_FIXED;

            _velocity += _gravity * timeDeltaNow; // gravity
            _velocity *= (1.0f - (_airFriction * timeDeltaNow)); // air friction formula

            rollRotation(timeDeltaNow);

            for (int n = 0; n < 3; ++n) {
                int i = n;
                if (n == 1) {i = 2;} // x,z,y (so gravity can stop it after x and z are processed)
                if (n == 2) {i = 1;}

                float prevPosition = position()[i];
                position()[i] += _velocity[i] * timeDeltaNow; // update pos

                glm::vec3 curAxeVelocity(0.0f);
                curAxeVelocity[i] = _velocity[i];

                float curVelLen = std::abs(_velocity[i]);

                CollisionResult result = collisionFalse();
                CollisionShape* resCollider = nullptr;
                for (CollisionShape* collider : allColliders) {
                    if (collider != this && collider->isEnabled()) {

                        // sphere mutualy exclusion of collision
                        float radius2 = std::max({collider->scale().x, collider->scale().y, collider->scale().z}) * 0.866f;
                        float totalRadius = radius1 + radius2 + curVelLen;
                        glm::vec3 diff = this->position() - collider->position();
                        float distSq = (diff.x * diff.x) + (diff.y * diff.y) + (diff.z * diff.z);
                        if (distSq > (totalRadius * totalRadius)) {
                            continue;
                        }

                        result = collider->collisionCheckDetailed(*this, curAxeVelocity, true);
                        if (result.collides) {
                            resCollider = collider;
                            break;
                        }
                    }
                }

                if (result.collides) { // if collides restore prev position
                    _isOnFloor = true;
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