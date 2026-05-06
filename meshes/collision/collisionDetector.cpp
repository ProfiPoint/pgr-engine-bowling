#include "collisionDetector.h"

namespace copakond {
    bool CollisionDetector::OBB1OOB2(const CollisionBox &box1, const CollisionBox &box2) { return false; }
    bool CollisionDetector::OOB1Sphere2(const CollisionBox &box1, const CollisionSphere &sphere2) { return false; }
    bool CollisionDetector::Sphere1OOB2(const CollisionSphere &sphere1, const CollisionBox &box2) { return OOB1Sphere2(box2, sphere1); }
    bool CollisionDetector::Sphere1Sphere2(const CollisionSphere &sphere1, const CollisionSphere &sphere2) { return false; }


    bool CollisionDetector::checkCollision(const CollisionBox* box1, const CollisionBox* box2) {
        bool collides = OBB1OOB2(*box1, *box2);
        return collides;
    }

    bool CollisionDetector::checkCollision(const CollisionBox* box1, const CollisionSphere* sphere2) {
            bool collides = OOB1Sphere2(*box1, *sphere2);
            return collides;
    }

    bool CollisionDetector::checkCollision(const CollisionSphere* sphere1, const CollisionBox* box2) {
            bool collides = Sphere1OOB2(*sphere1, *box2);
            return collides;
    }

    bool CollisionDetector::checkCollision(const CollisionSphere* sphere1, const CollisionSphere* sphere2) {
            bool collides = Sphere1Sphere2(*sphere1, *sphere2);
            return collides;
    }
}