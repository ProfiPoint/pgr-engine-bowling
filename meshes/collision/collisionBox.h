#ifndef PGR_SEM_COPAKOND_COLLISIONBOX_H
#define PGR_SEM_COPAKOND_COLLISIONBOX_H
#include "collisionShape.h"

namespace copakond {
    class CollisionBox : public CollisionShape {
    public:
        CollisionBox(const glm::vec3 &position = glm::vec3(0.0f), const glm::vec3 &rotation = glm::vec3(0.0f),
            const glm::vec3 &scale = glm::vec3(1.0f), bool visible = false);

        void init(GLuint shader) override;
        bool collisionCheck(const CollisionShape &mesh) override;
    };
}
#endif //PGR_SEM_COPAKOND_COLLISIONBOX_H
