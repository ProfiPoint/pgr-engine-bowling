#include "geometry.h"

namespace copakond {
    Geometry::Geometry() {
        _position = glm::vec3(0.0f, 0.0f, 0.0f);
        _rotation = glm::vec3(0.0f, 0.0f, 0.0f);
        _scale = glm::vec3(1.0f, 1.0f, 1.0f);
    }

    Geometry::Geometry(const glm::vec3 &position) {
        _position = position;
        _rotation = glm::vec3(0.0f, 0.0f, 0.0f);
        _scale = glm::vec3(1.0f, 1.0f, 1.0f);
    }

    Geometry::Geometry(const glm::vec3 &position, const glm::vec3 &rotation) {
        _position = position;
        _rotation = rotation;
        _scale = glm::vec3(1.0f, 1.0f, 1.0f);
    }

    Geometry::Geometry(const glm::vec3 &position, const glm::vec3 &rotation, const glm::vec3 &scale) {
        _position = position;
        _rotation = rotation;
        _scale = scale;
    }

    bool Geometry::setParent(Geometry *newParent) {
        if (newParent == this) {
            std::cerr << "Can't set parent to itself" << std::endl;
            return false;
        }

        Geometry *ancestor = newParent;
        while (ancestor != nullptr) {
            if (ancestor == this) {
                std::cerr << "Cycle detected: Cannot set self-descendant as a parent." << std::endl;
                return false;
            }
            ancestor = ancestor->parent;
        }

        this->parent = newParent;
        return true;
    }

    glm::mat4 Geometry::getRotationXMatrix() const {
        return glm::rotate(glm::mat4(1.0f), _rotation.x, glm::vec3(1, 0, 0));
    }

    glm::mat4 Geometry::getRotationYMatrix() const {
        return glm::rotate(glm::mat4(1.0f), _rotation.y, glm::vec3(0, 1, 0));
    }

    glm::mat4 Geometry::getRotationZMatrix() const {
        return glm::rotate(glm::mat4(1.0f), _rotation.z, glm::vec3(0, 0, 1));
    }

    glm::mat4 Geometry::getPositionMatrix() const {
        return glm::translate(glm::mat4(1.0f), _position);
    }

    glm::mat4 Geometry::getRotationMatrix() const {
        return getRotationZMatrix() * getRotationYMatrix() * getRotationXMatrix(); // Z * Y * X
    }

    glm::mat4 Geometry::getScaleMatrix() const {
        return glm::scale(glm::mat4(1.0f), _scale);
    }

    glm::mat4 Geometry::getModelMatrix() const {
        return getPositionMatrix() * getRotationMatrix() * getScaleMatrix();
    }
}
