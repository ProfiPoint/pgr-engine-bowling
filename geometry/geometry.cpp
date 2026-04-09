#include "geometry.h"

namespace copakond {
    Geometry::Geometry() {
        _translation = glm::vec3(0.0f, 0.0f, 0.0f);
        _rotation = glm::vec3(0.0f, 0.0f, 0.0f);
        _scale = glm::vec3(1.0f, 1.0f, 1.0f);
    }
    Geometry::Geometry(const glm::vec3& translation) {
        _translation = translation;
        _rotation = glm::vec3(0.0f, 0.0f, 0.0f);
        _scale = glm::vec3(1.0f, 1.0f, 1.0f);
    }
    Geometry::Geometry(const glm::vec3& translation, const glm::vec3& rotation) {
        _translation = translation;
        _rotation = rotation;
        _scale = glm::vec3(1.0f, 1.0f, 1.0f);
    }
    Geometry::Geometry(const glm::vec3& translation, const glm::vec3& rotation, const glm::vec3& scale) {
        _translation = translation;
        _rotation = rotation;
        _scale = scale;
    }

    glm::mat4 Geometry::getRotationXMatrix() const {
        return glm::rotate(glm::mat4(1.0f), _rotation.x, glm::vec3(1,0,0));
    }
    glm::mat4 Geometry::getRotationYMatrix() const {
        return glm::rotate(glm::mat4(1.0f), _rotation.y, glm::vec3(0,1,0));
    }
    glm::mat4 Geometry::getRotationZMatrix() const {
        return glm::rotate(glm::mat4(1.0f), _rotation.z, glm::vec3(0,0,1));
    }

    glm::mat4 Geometry::getTranslationMatrix() const {
        return glm::translate(glm::mat4(1.0f), _translation);
    }
    glm::mat4 Geometry::getRotationMatrix() const {
        return getRotationZMatrix() * getRotationYMatrix() * getRotationXMatrix(); // Z * Y * X
    }
    glm::mat4 Geometry::getScaleMatrix() const {
        return glm::scale(glm::mat4(1.0f), _scale);
    }

    glm::mat4 Geometry::getSRTMatrix() const {
        return getTranslationMatrix() * getRotationMatrix() * getScaleMatrix();
    }
}