#include "rigidSphere.h"

namespace copakond {
    RigidSphere::RigidSphere(const glm::vec3 &position, const glm::vec3 &rotation, const glm::vec3 &scale, float gravity, bool debug) :
    _gravity(gravity), CollisionSphere(position, rotation, scale, debug) {
        if (debug) {
            _material = std::make_shared<Material>();
            _material->ambient() = glm::vec3(1.0f, 0.6f, 0.0f);
            _material->diffuse() = glm::vec3(1.0f, 0.6f, 0.0f);
            _material->specular() = glm::vec3(0.0f, 0.0f, 0.0f);
            _material->alpha() = 0.25f;
        }
    }

    void RigidSphere::physics_process(float deltaTime, const std::vector<CollisionShape*>& allColliders) {
        // do collision check for all rigit bodies if i can fall
        // lets assume I can
        if (true) { // TODO check based of list of all collision boxes if i can fall (simulate the fall and then check if i can, if not return me back)
            _velocity.y -= _gravity * deltaTime;
            position() += _velocity * deltaTime;
        }
    }
}