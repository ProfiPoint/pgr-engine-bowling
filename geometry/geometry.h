#ifndef PGR_SEM_COPAKOND_GEOMETRY_H
#define PGR_SEM_COPAKOND_GEOMETRY_H

#include "pgr.h"

namespace copakond {
    class Geometry {
    private:
        glm::vec3 _translation;
        glm::vec3 _rotation; // radiant
        glm::vec3 _scale;
    public:
        Geometry();
        Geometry(const glm::vec3& translation);
        Geometry(const glm::vec3& translation, const glm::vec3& rotation);
        Geometry(const glm::vec3& translation, const glm::vec3& rotation, const glm::vec3& scale);

        // getters and setters in one
        glm::vec3& translation() { return _translation; }
        glm::vec3& rotation() { return _rotation; }
        glm::vec3& scale() { return _scale; }

        void setRotationDegrees(const glm::vec3& rotationDegrees) {  _rotation = glm::radians(rotationDegrees); }
        glm::vec3 getRotationDegrees() const { return glm::degrees(_rotation); }

        glm::mat4 getRotationXMatrix() const;
        glm::mat4 getRotationYMatrix() const;
        glm::mat4 getRotationZMatrix() const;

        glm::mat4 getTranslationMatrix() const;
        glm::mat4 getRotationMatrix() const;
        glm::mat4 getScaleMatrix() const;

        glm::mat4 getModelMatrix() const;
    };
}

#endif //PGR_SEM_COPAKOND_GEOMETRY_H