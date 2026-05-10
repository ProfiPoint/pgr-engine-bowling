#include "collisionPin.h"
#define FALL_SPEED 3.5f;
namespace copakond {

    CollisionPin::CollisionPin(const glm::vec3 &position, const glm::vec3 &rotation, const glm::vec3 &scale, bool visible)
        : CollisionSphere(position, rotation, scale, visible) {
        _startPosition = position;
        if (visible) {
            _material = std::make_shared<Material>();
            _material->ambient() = glm::vec3(1.0f, 0.0f, 0.0f);
            _material->diffuse() = glm::vec3(1.0f, 0.0f, 0.0f);
            _material->specular() = glm::vec3(0.0f, 0.0f, 0.0f);
            _material->alpha() = 0.25f;
        }
    }

    void CollisionPin::updatePin(float deltaTime, RigidSphere* ball) {
        if (!ball || !ball->isEnabled()) return;

        if (_state == PinState::IDLE) {
            CollisionResult res = CollisionSphere::collisionCheckDetailed(*ball, ball->velocity(), true);

            if (res.collides) {
                _state = PinState::FALLING;

                glm::vec3 flatVel = glm::normalize(glm::vec3(ball->velocity().x, 0.0f, ball->velocity().z));
                _fallAxis = glm::cross(glm::vec3(0.0f, 1.0f, 0.0f), flatVel);
                if (glm::length(_fallAxis) < 0.001f) { _fallAxis = glm::vec3(1.0f, 0.0f, 0.0f); }

                ball->velocity() *= 0.85f; // slowdown by 15 %
                ball->velocity() += res.normal * 1.5f; // more drastic reflection
            }
        }
        else if (_state == PinState::FALLING) {
            _fallAngle += deltaTime * FALL_SPEED;
            if (_fallAngle > glm::half_pi<float>()) {
                _fallAngle = glm::half_pi<float>();
                _state = PinState::DEAD;
            }
            rotation() = _fallAxis * _fallAngle;
        }
        else if (_state == PinState::DEAD) {
            _timeSinceHit += deltaTime;
            if (_timeSinceHit > 5.0f) {
                resetPin();
            }
        }
    }

    CollisionResult CollisionPin::collisionCheckDetailed(const CollisionShape &mesh, glm::vec3 velocity, bool calculateNormal) {
        CollisionResult result = CollisionSphere::collisionCheckDetailed(mesh, velocity, calculateNormal);
        result.collides = false;
        return result; // always false as it is a "trigger"
    }

    void CollisionPin::resetPin() {
        _state = PinState::IDLE;
        _fallAngle = 0.0f;
        _timeSinceHit = 0.0f;
        rotation() = glm::vec3(0.0f);
        position() = _startPosition;
    }

}