#include "collisionDetector.h"

namespace copakond {
    // using Separation Axis theorem.

    // copied. exact implementation of https://web.archive.org/web/19991129035017/http://www.gamasutra.com/features/19991018/Gomez_5.htm
    bool CollisionDetector::OBB1OOB2(const CollisionBox &box1, const CollisionBox &box2) {
        glm::vec3 pos1 = box1.getPosition();
        glm::vec3 rot1 = box1.getRotation();
        glm::vec3 siz1 = box1.getScale() / 2.0f;
        glm::vec3 pos2 = box2.getPosition();
        glm::vec3 rot2 = box2.getRotation();
        glm::vec3 siz2 = box2.getScale() / 2.0f;

        float radius1 = glm::length(siz1);
        float radius2 = glm::length(siz2);
        float dist = glm::length(pos2 - pos1);

        if (dist > (radius1 + radius2)) { return false; } // bouding sphere around the diagonal collision check

        // euler angles with orthonormal basis
        glm::mat3 Amat = glm::mat3(glm::quat(rot1));
        glm::mat3 Bmat = glm::mat3(glm::quat(rot2));

        glm::vec3 A[3] = { Amat[0], Amat[1], Amat[2] };
        glm::vec3 B[3] = { Bmat[0], Bmat[1], Bmat[2] };

        glm::vec3 v = pos2 - pos1; // world frame
        glm::vec3 T(glm::dot(v, A[0]), glm::dot(v, A[1]), glm::dot(v, A[2])); // box A coordinate system

        const float EPSILON = 1e-6f; // 0-div prevention

        // rotation matrix R calculation
        float R[3][3];
        float absR[3][3];
        for (int i = 0; i < 3; i++) {
            for (int k = 0; k < 3; k++) {
                R[i][k] = glm::dot(A[i], B[k]);
                absR[i][k] = std::abs(R[i][k]) + EPSILON;
            }
        }

        float ra, rb, t;

        // A basis vectors
        for (int i = 0; i < 3; i++) {
            ra = siz1[i];
            rb = siz2[0] * absR[i][0] + siz2[1] * absR[i][1] + siz2[2] * absR[i][2];
            t = std::abs(T[i]);
            if (t > ra + rb) return false;
        }

        // B basis vectors
        for (int k = 0; k < 3; k++) {
            ra = siz1[0] * absR[0][k] + siz1[1] * absR[1][k] + siz1[2] * absR[2][k];
            rb = siz2[k];
            t = std::abs(T[0] * R[0][k] + T[1] * R[1][k] + T[2] * R[2][k]);
            if (t > ra + rb) return false;
        }

        // L = A0 x B0
        ra = siz1[1] * absR[2][0] + siz1[2] * absR[1][0];
        rb = siz2[1] * absR[0][2] + siz2[2] * absR[0][1];
        t = std::abs(T[2] * R[1][0] - T[1] * R[2][0]);
        if (t > ra + rb) return false;

        // L = A0 x B1
        ra = siz1[1] * absR[2][1] + siz1[2] * absR[1][1];
        rb = siz2[0] * absR[0][2] + siz2[2] * absR[0][0];
        t = std::abs(T[2] * R[1][1] - T[1] * R[2][1]);
        if (t > ra + rb) return false;

        // L = A0 x B2
        ra = siz1[1] * absR[2][2] + siz1[2] * absR[1][2];
        rb = siz2[0] * absR[0][1] + siz2[1] * absR[0][0];
        t = std::abs(T[2] * R[1][2] - T[1] * R[2][2]);
        if (t > ra + rb) return false;

        // L = A1 x B0
        ra = siz1[0] * absR[2][0] + siz1[2] * absR[0][0];
        rb = siz2[1] * absR[1][2] + siz2[2] * absR[1][1];
        t = std::abs(T[0] * R[2][0] - T[2] * R[0][0]);
        if (t > ra + rb) return false;

        // L = A1 x B1
        ra = siz1[0] * absR[2][1] + siz1[2] * absR[0][1];
        rb = siz2[0] * absR[1][2] + siz2[2] * absR[1][0];
        t = std::abs(T[0] * R[2][1] - T[2] * R[0][1]);
        if (t > ra + rb) return false;

        // L = A1 x B2
        ra = siz1[0] * absR[2][2] + siz1[2] * absR[0][2];
        rb = siz2[0] * absR[1][1] + siz2[1] * absR[1][0];
        t = std::abs(T[0] * R[2][2] - T[2] * R[0][2]);
        if (t > ra + rb) return false;

        // L = A2 x B0
        ra = siz1[0] * absR[1][0] + siz1[1] * absR[0][0];
        rb = siz2[1] * absR[2][2] + siz2[2] * absR[2][1];
        t = std::abs(T[1] * R[0][0] - T[0] * R[1][0]);
        if (t > ra + rb) return false;

        // L = A2 x B1
        ra = siz1[0] * absR[1][1] + siz1[1] * absR[0][1];
        rb = siz2[0] * absR[2][2] + siz2[2] * absR[2][0];
        t = std::abs(T[1] * R[0][1] - T[0] * R[1][1]);
        if (t > ra + rb) return false;

        // L = A2 x B2
        ra = siz1[0] * absR[1][2] + siz1[1] * absR[0][2];
        rb = siz2[0] * absR[2][1] + siz2[1] * absR[2][0];
        t = std::abs(T[1] * R[0][2] - T[0] * R[1][2]);
        if (t > ra + rb) return false;

        return true; // no separation axe found
    }

    // assuming sphere is not an ellipsoid (MUST x=y=z)
    // copied and edited of https://www.geometrictools.com/Documentation/IntersectionBoxEllipsoid.pdf
    bool CollisionDetector::OOB1Sphere2(const CollisionBox &box1, const CollisionSphere &sphere2) {
        glm::vec3 boxPos = box1.getPosition();
        glm::vec3 boxRot = box1.getRotation();
        glm::vec3 boxHalfExtents = box1.getScale() / 2.0f;

        glm::vec3 spherePos = sphere2.getPosition();
        float sphereRadius = sphere2.getScale().x / 2.0f;

        // orthonormal basis
        glm::mat3 boxMat = glm::mat3(glm::quat(boxRot));
        glm::vec3 A[3] = { boxMat[0], boxMat[1], boxMat[2] };

        glm::vec3 v = spherePos - boxPos; // world frame
        glm::vec3 localSpherePos( // box A coordinate system
            glm::dot(v, A[0]),
            glm::dot(v, A[1]),
            glm::dot(v, A[2])
        );

        glm::vec3 closestPoint = glm::clamp(localSpherePos, -boxHalfExtents, boxHalfExtents); // closest point on the OBB to the sphere center
        glm::vec3 diff = localSpherePos - closestPoint; // distance between the point
        float distanceSq = glm::dot(diff, diff); // ||diff||^2
        return distanceSq <= (sphereRadius * sphereRadius); // check if the distance^2  collides with the sphere
    }

    bool CollisionDetector::Sphere1OOB2(const CollisionSphere &sphere1, const CollisionBox &box2) { return OOB1Sphere2(box2, sphere1); }

    // assuming the spheres are spheres not ellipsoids (MUST x=y=z).
    bool CollisionDetector::Sphere1Sphere2(const CollisionSphere &sphere1, const CollisionSphere &sphere2) {
        float size1x = sphere1.getScale().x / 2.0f;
        float size2x = sphere2.getScale().x / 2.0f;
        float distance = glm::distance(sphere1.getPosition(), sphere2.getPosition());
        if (distance < size1x + size2x) { return true; }
        return false;
    }


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

    bool CollisionDetector::checkCollision(const CollisionShape* shape1, const CollisionShape* shape2) {
        // check if its a given type
        const CollisionBox* box1 = dynamic_cast<const CollisionBox*>(shape1);
        const CollisionBox* box2 = dynamic_cast<const CollisionBox*>(shape2);
        const CollisionSphere* sphere1 = dynamic_cast<const CollisionSphere*>(shape1);
        const CollisionSphere* sphere2 = dynamic_cast<const CollisionSphere*>(shape2);

        // check collisions
        if (box1 && box2) { return checkCollision(box1, box2); }
        else if (box1 && sphere2) { return checkCollision(box1, sphere2); }
        else if (sphere1 && box2) { return checkCollision(sphere1, box2); }
        else if (sphere1 && sphere2) { return checkCollision(sphere1, sphere2); }

        return false;
    }
}