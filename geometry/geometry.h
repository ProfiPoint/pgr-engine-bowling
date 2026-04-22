#ifndef PGR_SEM_COPAKOND_GEOMETRY_H
#define PGR_SEM_COPAKOND_GEOMETRY_H

#include "../pgr-portable.h"

namespace copakond {
    class Geometry {
    protected:
        glm::vec3 _translation;
        glm::vec3 _rotation; // radiant
        glm::vec3 _scale;

    public:
        Geometry();
        Geometry(const glm::vec3 &translation);
        Geometry(const glm::vec3 &translation, const glm::vec3 &rotation);
        Geometry(const glm::vec3 &translation, const glm::vec3 &rotation, const glm::vec3 &scale);

        // getters and setters in one
        virtual void setTranslation(const glm::vec3& translation) { _translation = translation; }
        virtual void setRotation(const glm::vec3& rotation) { _rotation = rotation; }
        virtual void setScale(const glm::vec3& scale) { _scale = scale; }
        virtual void setRotationDegrees(const glm::vec3 &rotationDegrees) { _rotation = glm::radians(rotationDegrees); }

        glm::mat4 getRotationXMatrix() const;
        glm::mat4 getRotationYMatrix() const;
        glm::mat4 getRotationZMatrix() const;

        glm::mat4 getTranslationMatrix() const;
        glm::mat4 getRotationMatrix() const;
        glm::mat4 getScaleMatrix() const;
        glm::mat4 getModelMatrix() const;

        glm::vec3 getTranslation() const { return _translation; }
        glm::vec3 getRotation() const { return _rotation; }
        glm::vec3 getScale() const { return _scale; }
        glm::vec3 getRotationDegrees() const { return glm::degrees(_rotation); }
    };
}

#endif //PGR_SEM_COPAKOND_GEOMETRY_H
