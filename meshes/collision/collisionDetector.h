#ifndef PGR_SEM_COPAKOND_COLLISIONDETECTOR_H
#define PGR_SEM_COPAKOND_COLLISIONDETECTOR_H

#include "../../pgr-portable.h"

namespace copakond {
    class CollisionShape; // circular include dependency fix
    class CollisionBox;
    class CollisionSphere;

    struct CollisionResult {
        bool collides = false;
        glm::vec3 normal = glm::vec3(0.0f);
        glm::vec3 reflection = glm::vec3(0.0f);
    };

    CollisionResult collisionFalse();
    CollisionResult collisionTrue(const glm::vec3 &normal, const glm::vec3 &reflection);

    class CollisionDetector {
    private:
        static CollisionResult OBB1OOB2(const CollisionBox &box1, const CollisionBox &box2, glm::vec3 velocity);
        static CollisionResult OOB1Sphere2(const CollisionBox &box1, const CollisionSphere &box2, glm::vec3 velocity);
        static CollisionResult Sphere1OOB2(const CollisionSphere &box1, const CollisionBox &box2, glm::vec3 velocity);
        static CollisionResult Sphere1Sphere2(const CollisionSphere &box1, const CollisionSphere &box2, glm::vec3 velocity);
    public:
        CollisionDetector() {}

        static CollisionResult checkCollision(const CollisionBox* box1, const CollisionBox* box2, glm::vec3 velocity = glm::vec3(0.0f));
        static CollisionResult checkCollision(const CollisionBox* box, const CollisionSphere* sphere, glm::vec3 velocity = glm::vec3(0.0f));
        static CollisionResult checkCollision(const CollisionSphere* sphere, const CollisionBox* box, glm::vec3 velocity = glm::vec3(0.0f));
        static CollisionResult checkCollision(const CollisionSphere* sphere1, const CollisionSphere* sphere2, glm::vec3 velocity = glm::vec3(0.0f));

        static CollisionResult checkCollision(const CollisionShape* shape1, const CollisionShape* shape2, glm::vec3 velocity = glm::vec3(0.0f));
    };
}

#endif //PGR_SEM_COPAKOND_COLLISIONDETECTOR_H
