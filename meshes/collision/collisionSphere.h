#ifndef PGR_SEM_COPAKOND_COLLISIONSPHERE_H
#define PGR_SEM_COPAKOND_COLLISIONSPHERE_H
#include "collisionShape.h"
#include "collisionDetector.h"

namespace copakond {
    class CollisionSphere : public CollisionShape {
    public:
        CollisionSphere(const glm::vec3 &position = glm::vec3(0.0f), const glm::vec3 &rotation = glm::vec3(0.0f),
            const glm::vec3 &scale = glm::vec3(1.0f), bool visible = false);

        void init(GLuint shader) override;
        bool collisionCheck(const CollisionShape &mesh, glm::vec3 velocity = glm::vec3(0.0f)) override;
        CollisionResult collisionCheckDetailed(const CollisionShape &mesh, glm::vec3 velocity) override;
    };
}

#endif //PGR_SEM_COPAKOND_COLLISIONSPHERE_H
