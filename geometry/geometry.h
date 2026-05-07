#ifndef PGR_SEM_COPAKOND_GEOMETRY_H
#define PGR_SEM_COPAKOND_GEOMETRY_H

#include "../pgr-portable.h"
#include <iostream>

namespace copakond {
    class Geometry {
    protected:
        Geometry *parent = nullptr;
        std::vector<Geometry*> children;

        glm::vec3 _position;
        glm::vec3 _rotation; // radiants
        glm::vec3 _scale;

    public:
        Geometry();
        Geometry(const glm::vec3 &position);
        Geometry(const glm::vec3 &position, const glm::vec3 &rotation);
        Geometry(const glm::vec3 &position, const glm::vec3 &rotation, const glm::vec3 &scale);
        virtual ~Geometry();

        // getters and setters in one
        virtual void setPosition(const glm::vec3& position) { _position = position; }
        virtual void setRotation(const glm::vec3& rotation) { _rotation = rotation; }
        virtual void setScale(const glm::vec3& scale) { _scale = scale; }
        virtual void setRotationDegrees(const glm::vec3 &rotationDegrees) { _rotation = glm::radians(rotationDegrees); }

        glm::mat4 getRotationXMatrix() const;
        glm::mat4 getRotationYMatrix() const;
        glm::mat4 getRotationZMatrix() const;

        // local
        glm::mat4 getPositionMatrix() const;
        glm::mat4 getRotationMatrix() const;
        glm::mat4 getScaleMatrix() const;
        glm::mat4 getModelMatrix() const; // local matrix

        // world position
        glm::mat4 getWorldPositionMatrix() const;
        glm::mat4 getWorldRotationMatrix() const;
        glm::mat4 getWorldScaleMatrix() const;
        glm::mat4 getWorldModelMatrix() const; // used for shader (all matrixes of all ancestors multiplied)

        glm::vec3 getPosition() const { return _position; }
        glm::vec3 getRotation() const { return _rotation; }
        glm::vec3 getScale() const { return _scale; }
        glm::vec3 getRotationDegrees() const { return glm::degrees(_rotation); }

        glm::vec3 getWorldPosition() const;
        glm::vec3 getWorldRotation() const;
        glm::vec3 getWorldScale() const;

        glm::vec3& position() { return _position; }
        glm::vec3& rotation() { return _rotation; }
        glm::vec3& scale() { return _scale; }

        glm::vec3 worldPosition() const;
        glm::vec3 worldRotation() const;
        glm::vec3 worldScale() const;

        bool setParent(Geometry *newParent);
        Geometry* getParent() const { return parent; }
        std::vector<Geometry*> getChildren() const { return children; }
    };
}

#endif //PGR_SEM_COPAKOND_GEOMETRY_H
