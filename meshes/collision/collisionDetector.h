#ifndef PGR_SEM_COPAKOND_COLLISIONDETECTOR_H
#define PGR_SEM_COPAKOND_COLLISIONDETECTOR_H
#include "collisionBox.h"
#include "collisionSphere.h"

namespace copakond {
    class CollisionDetector {
    private:
        bool OBB1OOB2(CollisionBox box1, CollisionBox box2) { return false; }
        bool OOB1Sphere2(CollisionBox box1, CollisionSphere box2) { return false; }
        bool Sphere1OOB2(CollisionSphere box1, CollisionBox box2) { return false; }
        bool Sphere1Sphere2(CollisionSphere box1, CollisionSphere box2) { return false; }
    public:
        CollisionDetector() {}
        bool checkCollision(CollisionBox *mesh1, CollisionBox *mesh2) { return false; }
    };
}

#endif //PGR_SEM_COPAKOND_COLLISIONDETECTOR_H
