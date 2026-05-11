#include "collisionPin.h"
#define FALL_SPEED 3.5f

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
            glm::vec3 diff = ball->position() - this->position();
            float distSq = glm::dot(diff, diff);
            float combinedRadius = (this->scale().x * 0.5f) + (ball->scale().x * 0.5f);

            // custom sphere collision calculation
            if (distSq < (combinedRadius * combinedRadius)) {
                _state = PinState::FALLING;

                glm::vec3 flatVel = glm::normalize(glm::vec3(ball->velocity().x, 0.0f, ball->velocity().z));
                _fallAxis = glm::cross(glm::vec3(0.0f, 1.0f, 0.0f), flatVel);
                if (glm::length(_fallAxis) < 0.001f) { _fallAxis = glm::vec3(1.0f, 0.0f, 0.0f); }

                glm::vec3 fastNormal = glm::normalize(diff);

                ball->velocity() *= 0.90f; // slowdown by 10 %
                ball->velocity() += fastNormal * 0.25f; // flings little bit
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
    }

    CollisionResult CollisionPin::collisionCheckDetailed(const CollisionShape &mesh, glm::vec3 velocity, bool calculateNormal) {
        if (_state != PinState::IDLE) {
            CollisionResult res;
            res.collides = false;
            return res;
        }

        CollisionResult result = CollisionSphere::collisionCheckDetailed(mesh, velocity, calculateNormal);
        result.collides = false;
        return result;
    }

    void CollisionPin::reset() {
        _state = PinState::IDLE;
        _fallAngle = 0.0f;
        _timeSinceHit = 0.0f;
        rotation() = glm::vec3(0.0f);
        position() = _startPosition;
    }
}