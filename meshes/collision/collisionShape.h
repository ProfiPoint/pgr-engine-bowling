#ifndef PGR_SEM_COPAKOND_COLLISIONSHAPE_H
#define PGR_SEM_COPAKOND_COLLISIONSHAPE_H

#define DELTA_TIME_FIXED (1.0f / 20.0f)
#include "../mesh.h"
#include "collisionDetector.h"

namespace copakond {
    enum class ShapeType { BOX, SPHERE };

    /** @brief Physical properties affecting collision resolution */
    struct PhysicsMaterial {
        float bounciness = 0.05f; /**< 0 = no bounce, 1 = full energy retention */
        float friction = 0.95f; /**< 0 = no friction, 1 = instant stop on slide */
    };

    /** @brief Base class for physics colliders, acting as an invisible (or debug) mesh */
    class CollisionShape : public Mesh {
    protected:
        bool _enabled = true;

        void _generateGeometry(GLuint shader, const std::vector<float>& vertices, const std::vector<float>& normals);

    public:
        ShapeType shapeType;
        PhysicsMaterial physicsMaterial = PhysicsMaterial();

        CollisionShape(const glm::vec3 &position = glm::vec3(0.0f), const glm::vec3 &rotation = glm::vec3(0.0f),
            const glm::vec3 &scale = glm::vec3(1.0f), bool visible = false);

        void draw(float deltaTime) override;

        void enable() { _enabled = true; }
        void disable() { _enabled = false; }
        bool isEnabled() const { return _enabled; }

        /** @brief Fast boolean check if this shape intersects with another */
        virtual bool collisionCheck(const CollisionShape &mesh, glm::vec3 velocity) = 0;

        /** @brief Detailed collision check returning overlap status, normal, and reflection vectors */
        virtual CollisionResult collisionCheckDetailed(const CollisionShape &mesh, glm::vec3 velocity, bool calculateNormal = false) = 0;
    };
}

#endif //PGR_SEM_COPAKOND_COLLISIONSHAPE_H