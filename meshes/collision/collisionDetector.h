#ifndef PGR_SEM_COPAKOND_COLLISIONDETECTOR_H
#define PGR_SEM_COPAKOND_COLLISIONDETECTOR_H
#include "collisionBox.h"
#include "collisionSphere.h"

namespace copakond {
    class CollisionDetector {
    private:
        static bool OBB1OOB2(const CollisionBox &box1, const CollisionBox &box2);
        static bool OOB1Sphere2(const CollisionBox &box1, const CollisionSphere &box2);
        static bool Sphere1OOB2(const CollisionSphere &box1, const CollisionBox &box2);
        static bool Sphere1Sphere2(const CollisionSphere &box1, const CollisionSphere &box2);
    public:
        CollisionDetector() {}

        static bool checkCollision(const CollisionBox* box1, const CollisionBox* box2);
        static bool checkCollision(const CollisionBox* box, const CollisionSphere* sphere);
        static bool checkCollision(const CollisionSphere* sphere, const CollisionBox* box);
        static bool checkCollision(const CollisionSphere* sphere1, const CollisionSphere* sphere2);

        static bool checkCollision(const CollisionShape* shape1, const CollisionShape* shape2);
    };
}

#endif //PGR_SEM_COPAKOND_COLLISIONDETECTOR_H
