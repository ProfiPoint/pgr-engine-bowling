#ifndef PGR_SEM_COPAKOND_COLLISIONSHAPE_H
#define PGR_SEM_COPAKOND_COLLISIONSHAPE_H

#define DELTA_TIME_FIXED (1.0f / 60.0f)
#include "../mesh.h"
#include "collisionDetector.h"

namespace copakond {
    struct PhysicsMaterial {
        float bounciness = 0.5f; // 0 = no bounce, 1 = full bounce
        float friction = 0.2f; // 0 = no friction, 1 = instant stop
    };

    class CollisionShape : public Mesh {
    protected:
        bool _enabled = true;

        void _generateGeometry(GLuint shader, const std::vector<float>& vertices, const std::vector<float>& normals);

    public:
        PhysicsMaterial physicsMaterial = PhysicsMaterial();

        CollisionShape(const glm::vec3 &position = glm::vec3(0.0f), const glm::vec3 &rotation = glm::vec3(0.0f),
            const glm::vec3 &scale = glm::vec3(1.0f), bool visible = false);

        void draw(float deltaTime) override;

        void enable() { _enabled = true; }
        void disable() { _enabled = false; }
        bool isEnabled() const { return _enabled; }

        virtual bool collisionCheck(const CollisionShape &mesh, glm::vec3 velocity) = 0; // virtual
        virtual CollisionResult collisionCheckDetailed(const CollisionShape &mesh, glm::vec3 velocity, bool calculateNormal = false) = 0; // virtual
    };
}

#endif //PGR_SEM_COPAKOND_COLLISIONSHAPE_H