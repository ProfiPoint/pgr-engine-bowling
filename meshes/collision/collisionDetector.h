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
        static glm::vec3 OBB1OBB2Normal(const CollisionBox &box1, const CollisionBox &box2);
        static glm::vec3 OBB1Sphere2Normal(const CollisionBox &box1, const CollisionSphere &box2);
        static glm::vec3 Sphere1Sphere2Normal(const CollisionSphere &box1, const CollisionSphere &box2);

        static CollisionResult OBB1OBB2(const CollisionBox &box1, const CollisionBox &box2, glm::vec3 velocity, bool calculateNormal = false);
        static CollisionResult OBB1Sphere2(const CollisionBox &box1, const CollisionSphere &box2, glm::vec3 velocity, bool calculateNormal = false);
        static CollisionResult Sphere1Sphere2(const CollisionSphere &box1, const CollisionSphere &box2, glm::vec3 velocity, bool calculateNormal = false);
    public:
        CollisionDetector() {}

        static CollisionResult checkCollision(const CollisionBox* box1, const CollisionBox* box2, const glm::vec3 &velocity = glm::vec3(0.0f), bool calculateNormal = false);
        static CollisionResult checkCollision(const CollisionBox* box, const CollisionSphere* sphere, const glm::vec3 &velocity = glm::vec3(0.0f), bool calculateNormal = false);
        static CollisionResult checkCollision(const CollisionSphere* sphere, const CollisionBox* box, const glm::vec3 &velocity = glm::vec3(0.0f), bool calculateNormal = false);
        static CollisionResult checkCollision(const CollisionSphere* sphere1, const CollisionSphere* sphere2, const glm::vec3 &velocity = glm::vec3(0.0f), bool calculateNormal = false);

        static CollisionResult checkCollision(const CollisionShape* shape1, const CollisionShape* shape2, const glm::vec3 &velocity = glm::vec3(0.0f), bool calculateNormal = false);
    };
}

#endif //PGR_SEM_COPAKOND_COLLISIONDETECTOR_H
