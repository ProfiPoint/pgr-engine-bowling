#include "collisionDetector.h"
#include "collisionBox.h"
#include "collisionSphere.h"
#include "collisionShape.h"

namespace copakond {
    CollisionResult collisionFalse() {
        CollisionResult result;
        result.collides = false;
        return result;
    }

    CollisionResult collisionTrue(const glm::vec3 &normal, const glm::vec3 &reflection) {
        CollisionResult result;
        result.collides = true;
        result.normal = normal;
        result.reflection = reflection;
        return result;
    }


    // COLLISION NORMAL CALCULATION
    // https://www.reddit.com/r/gamedev/comments/brb88i/question_bout_obb_collision_detection/ for normal calcualtion
    glm::vec3 CollisionDetector::OBB1OBB2Normal(const CollisionBox &box1, const CollisionBox &box2) {
        glm::vec3 pos1 = box1.getPosition();
        glm::vec3 rot1 = box1.getRotation();
        glm::vec3 siz1 = box1.getScale() / 2.0f;
        glm::vec3 pos2 = box2.getPosition();
        glm::vec3 rot2 = box2.getRotation();
        glm::vec3 siz2 = box2.getScale() / 2.0f;

        // euler angles with orthonormal basis
        glm::mat3 Amat = glm::mat3(glm::quat(rot1));
        glm::mat3 Bmat = glm::mat3(glm::quat(rot2));

        glm::vec3 A[3] = { Amat[0], Amat[1], Amat[2] };
        glm::vec3 B[3] = { Bmat[0], Bmat[1], Bmat[2] };

        glm::vec3 v = pos2 - pos1; // world frame diff distance

        // all separation axes
        glm::vec3 axes[15] = {
            A[0], A[1], A[2],
            B[0], B[1], B[2],
            glm::cross(A[0], B[0]), glm::cross(A[0], B[1]), glm::cross(A[0], B[2]),
            glm::cross(A[1], B[0]), glm::cross(A[1], B[1]), glm::cross(A[1], B[2]),
            glm::cross(A[2], B[0]), glm::cross(A[2], B[1]), glm::cross(A[2], B[2])
        };

        float minOverlap = std::numeric_limits<float>::max();
        glm::vec3 minAxis = glm::vec3(0.0f, 1.0f, 0.0f); // if not found, or float errors

        // searching for the min "Penetration Axe"
        for (int i = 0; i < 15; i++) {
            glm::vec3 axis = glm::normalize(axes[i]);

            float lengthSq = glm::dot(axis, axis);
            if (lengthSq < 0.001f) { continue; } // zero div prev, would be inf.

            // projection of A, B to world coord.
            float rA = siz1.x * std::abs(glm::dot(A[0], axis)) + siz1.y * std::abs(glm::dot(A[1], axis)) + siz1.z * std::abs(glm::dot(A[2], axis));
            float rB = siz2.x * std::abs(glm::dot(B[0], axis)) + siz2.y * std::abs(glm::dot(B[1], axis)) + siz2.z * std::abs(glm::dot(B[2], axis));

            float distProj = std::abs(glm::dot(v, axis)); // distance of the proj
            float overlap = (rA + rB) - distProj; // total overlap

            if (overlap < minOverlap) { // min overlap
                minOverlap = overlap;
                minAxis = axis;
            }
        }

        // axe will must point out always
        if (glm::dot(minAxis, v) > 0.0f) {
            minAxis = -minAxis;
        }

        return minAxis;
    }


    // COLLISION DETECTION

    // using Separation Axis theorem.
    // copied. exact implementation of https://web.archive.org/web/19991129035017/http://www.gamasutra.com/features/19991018/Gomez_5.htm
    CollisionResult CollisionDetector::OBB1OBB2(const CollisionBox &box1, const CollisionBox &box2, glm::vec3 velocity, bool calculateNormal) {
        glm::vec3 pos1 = box1.getPosition();
        glm::vec3 rot1 = box1.getRotation();
        glm::vec3 siz1 = box1.getScale() / 2.0f;
        glm::vec3 pos2 = box2.getPosition();
        glm::vec3 rot2 = box2.getRotation();
        glm::vec3 siz2 = box2.getScale() / 2.0f;

        float radius1 = glm::length(siz1);
        float radius2 = glm::length(siz2);
        float dist = glm::length(pos2 - pos1);

        if (dist > (radius1 + radius2)) { return collisionFalse(); } // bouding sphere around the diagonal collision check

        // euler angles with orthonormal basis
        glm::mat3 Amat = glm::mat3(glm::quat(rot1));
        glm::mat3 Bmat = glm::mat3(glm::quat(rot2));

        glm::vec3 A[3] = { Amat[0], Amat[1], Amat[2] };
        glm::vec3 B[3] = { Bmat[0], Bmat[1], Bmat[2] };

        glm::vec3 v = pos2 - pos1; // world frame diff distance
        glm::vec3 T(glm::dot(v, A[0]), glm::dot(v, A[1]), glm::dot(v, A[2])); // box A coordinate system

        // rotation matrix R calculation
        float R[3][3];
        float absR[3][3];
        for (int i = 0; i < 3; i++) {
            for (int k = 0; k < 3; k++) {
                R[i][k] = glm::dot(A[i], B[k]);
                absR[i][k] = std::abs(R[i][k]) + 0.00001f; // preventing 0 division
            }
        }

        float ra, rb, t;

        // A basis vectors
        for (int i = 0; i < 3; i++) {
            ra = siz1[i];
            rb = siz2[0] * absR[i][0] + siz2[1] * absR[i][1] + siz2[2] * absR[i][2];
            t = std::abs(T[i]);
            if (t > ra + rb) return collisionFalse();
        }

        // B basis vectors
        for (int k = 0; k < 3; k++) {
            ra = siz1[0] * absR[0][k] + siz1[1] * absR[1][k] + siz1[2] * absR[2][k];
            rb = siz2[k];
            t = std::abs(T[0] * R[0][k] + T[1] * R[1][k] + T[2] * R[2][k]);
            if (t > ra + rb) return collisionFalse();
        }

        // L = A0 x B0
        ra = siz1[1] * absR[2][0] + siz1[2] * absR[1][0];
        rb = siz2[1] * absR[0][2] + siz2[2] * absR[0][1];
        t = std::abs(T[2] * R[1][0] - T[1] * R[2][0]);
        if (t > ra + rb) return collisionFalse();

        // L = A0 x B1
        ra = siz1[1] * absR[2][1] + siz1[2] * absR[1][1];
        rb = siz2[0] * absR[0][2] + siz2[2] * absR[0][0];
        t = std::abs(T[2] * R[1][1] - T[1] * R[2][1]);
        if (t > ra + rb) return collisionFalse();

        // L = A0 x B2
        ra = siz1[1] * absR[2][2] + siz1[2] * absR[1][2];
        rb = siz2[0] * absR[0][1] + siz2[1] * absR[0][0];
        t = std::abs(T[2] * R[1][2] - T[1] * R[2][2]);
        if (t > ra + rb) return collisionFalse();

        // L = A1 x B0
        ra = siz1[0] * absR[2][0] + siz1[2] * absR[0][0];
        rb = siz2[1] * absR[1][2] + siz2[2] * absR[1][1];
        t = std::abs(T[0] * R[2][0] - T[2] * R[0][0]);
        if (t > ra + rb) return collisionFalse();

        // L = A1 x B1
        ra = siz1[0] * absR[2][1] + siz1[2] * absR[0][1];
        rb = siz2[0] * absR[1][2] + siz2[2] * absR[1][0];
        t = std::abs(T[0] * R[2][1] - T[2] * R[0][1]);
        if (t > ra + rb) return collisionFalse();

        // L = A1 x B2
        ra = siz1[0] * absR[2][2] + siz1[2] * absR[0][2];
        rb = siz2[0] * absR[1][1] + siz2[1] * absR[1][0];
        t = std::abs(T[0] * R[2][2] - T[2] * R[0][2]);
        if (t > ra + rb) return collisionFalse();

        // L = A2 x B0
        ra = siz1[0] * absR[1][0] + siz1[1] * absR[0][0];
        rb = siz2[1] * absR[2][2] + siz2[2] * absR[2][1];
        t = std::abs(T[1] * R[0][0] - T[0] * R[1][0]);
        if (t > ra + rb) return collisionFalse();

        // L = A2 x B1
        ra = siz1[0] * absR[1][1] + siz1[1] * absR[0][1];
        rb = siz2[0] * absR[2][2] + siz2[2] * absR[2][0];
        t = std::abs(T[1] * R[0][1] - T[0] * R[1][1]);
        if (t > ra + rb) return collisionFalse();

        // L = A2 x B2
        ra = siz1[0] * absR[1][2] + siz1[1] * absR[0][2];
        rb = siz2[0] * absR[2][1] + siz2[1] * absR[2][0];
        t = std::abs(T[1] * R[0][2] - T[0] * R[1][2]);
        if (t > ra + rb) return collisionFalse();

        // no separation axe found
        if (calculateNormal) {
            glm::vec3 normal = OBB1OBB2Normal(box1, box2);
            glm::vec3 reflection = glm::reflect(velocity, normal);
            return collisionTrue(normal, reflection);
        } else {
            return collisionTrue(glm::vec3(0.0f), glm::vec3(0.0f));
        }

    }

    // assuming sphere is not an ellipsoid (MUST x=y=z)
    // copied and edited of https://www.geometrictools.com/Documentation/IntersectionBoxEllipsoid.pdf
    CollisionResult CollisionDetector::OBB1Sphere2(const CollisionBox &box1, const CollisionSphere &sphere2, glm::vec3 velocity, bool calculateNormal) {
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
        if (distanceSq <= (sphereRadius * sphereRadius)) { // check if the distance^2  collides with the sphere
            // https://gamedev.net/tag/community/forums/topic.asp?topic_id=555502
            if (calculateNormal) {
                glm::vec3 worldDiff = (diff.x * A[0]) + (diff.y * A[1]) + (diff.z * A[2]); // local diff in world space

                glm::vec3 normal = glm::vec3(0.0f, 1.0f, 0.0f); // if centered
                if (glm::length(worldDiff) > 0.001f) { // not centered
                    normal = glm::normalize(-worldDiff); // flip to make it Sphere to Box
                }

                glm::vec3 reflection = glm::reflect(velocity, normal);
                return collisionTrue(normal, reflection);
            } else {
                return collisionTrue(glm::vec3(0.0f), glm::vec3(0.0f));
            }
        } else {
            return collisionFalse();
        }
    }

    // assuming the spheres are spheres not ellipsoids (MUST x=y=z).
    CollisionResult CollisionDetector::Sphere1Sphere2(const CollisionSphere &sphere1, const CollisionSphere &sphere2, glm::vec3 velocity, bool calculateNormal) {
        float size1x = sphere1.getScale().x / 2.0f;
        float size2x = sphere2.getScale().x / 2.0f;
        float distance = glm::distance(sphere1.getPosition(), sphere2.getPosition());
        if (distance < size1x + size2x) {
            if (calculateNormal) {
                glm::vec3 normal = glm::normalize(sphere1.getPosition() - sphere2.getPosition()); // diff between possition
                glm::vec3 reflection = glm::reflect(velocity, normal);
                return collisionTrue(normal, reflection);
            } else {
                return collisionTrue(glm::vec3(0.0f), glm::vec3(0.0f));
            }
        } else {
            return collisionFalse();
        }
    }



    // Public callers
    CollisionResult CollisionDetector::checkCollision(const CollisionBox* box1, const CollisionBox* box2, const glm::vec3 &velocity, bool calculateNormal) {
        CollisionResult collides = OBB1OBB2(*box1, *box2, velocity, calculateNormal);
        return collides;
    }

    CollisionResult CollisionDetector::checkCollision(const CollisionBox* box1, const CollisionSphere* sphere2, const glm::vec3 &velocity, bool calculateNormal) {
        CollisionResult collides = OBB1Sphere2(*box1, *sphere2, velocity, calculateNormal);
        return collides;
    }

    CollisionResult CollisionDetector::checkCollision(const CollisionSphere* sphere1, const CollisionBox* box2, const glm::vec3 &velocity, bool calculateNormal) {
        CollisionResult collides = OBB1Sphere2(*box2, *sphere1, velocity, calculateNormal);
        return collides;
    }

    CollisionResult CollisionDetector::checkCollision(const CollisionSphere* sphere1, const CollisionSphere* sphere2, const glm::vec3 &velocity, bool calculateNormal) {
        CollisionResult collides = Sphere1Sphere2(*sphere1, *sphere2, velocity, calculateNormal);
        return collides;
    }

    CollisionResult CollisionDetector::checkCollision(const CollisionShape* shape1, const CollisionShape* shape2, const glm::vec3 &velocity, bool calculateNormal) {
        // check if its a given type
        const CollisionBox* box1 = dynamic_cast<const CollisionBox*>(shape1);
        const CollisionBox* box2 = dynamic_cast<const CollisionBox*>(shape2);
        const CollisionSphere* sphere1 = dynamic_cast<const CollisionSphere*>(shape1);
        const CollisionSphere* sphere2 = dynamic_cast<const CollisionSphere*>(shape2);

        // check collisions
        if (box1 && box2) { return checkCollision(box1, box2, velocity, calculateNormal); }
        else if (box1 && sphere2) { return checkCollision(box1, sphere2, velocity, calculateNormal); }
        else if (sphere1 && box2) { return checkCollision(sphere1, box2, velocity, calculateNormal); }
        else if (sphere1 && sphere2) { return checkCollision(sphere1, sphere2, velocity, calculateNormal); }

        return collisionFalse();
    }
}