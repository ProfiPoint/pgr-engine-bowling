#include "collisionBox.h"
#include "collisionDetector.h"

namespace copakond {
    CollisionBox::CollisionBox(const glm::vec3 &position, const glm::vec3 &rotation, const glm::vec3 &scale, bool visible)
        : CollisionShape(position, rotation, scale, visible) {}

    void CollisionBox::init(GLuint shader) {
        _shaderProgram = shader;

        // Define the 36 vertices of a 1x1x1 cube centered at origin
        std::vector<float> vertices = {
            // back
            1.0f/2,  1.0f/2, -1.0f/2,
           -1.0f/2,  1.0f/2, -1.0f/2,
           -1.0f/2, -1.0f/2, -1.0f/2,

           -1.0f/2, -1.0f/2, -1.0f/2,
            1.0f/2, -1.0f/2, -1.0f/2,
            1.0f/2,  1.0f/2, -1.0f/2,

           // front
            1.0f/2,  1.0f/2,  1.0f/2,
            1.0f/2, -1.0f/2,  1.0f/2,
           -1.0f/2, -1.0f/2,  1.0f/2,

           -1.0f/2, -1.0f/2,  1.0f/2,
           -1.0f/2,  1.0f/2,  1.0f/2,
            1.0f/2,  1.0f/2,  1.0f/2,

           // left
           -1.0f/2, -1.0f/2, -1.0f/2,
           -1.0f/2,  1.0f/2, -1.0f/2,
           -1.0f/2,  1.0f/2,  1.0f/2,

           -1.0f/2,  1.0f/2,  1.0f/2,
           -1.0f/2, -1.0f/2,  1.0f/2,
           -1.0f/2, -1.0f/2, -1.0f/2,

           // right
            1.0f/2,  1.0f/2, -1.0f/2,
            1.0f/2, -1.0f/2, -1.0f/2,
            1.0f/2,  1.0f/2,  1.0f/2,

            1.0f/2, -1.0f/2,  1.0f/2,
            1.0f/2,  1.0f/2,  1.0f/2,
            1.0f/2, -1.0f/2, -1.0f/2,

           // bottom
            1.0f/2, -1.0f/2,  1.0f/2,
            1.0f/2, -1.0f/2, -1.0f/2,
           -1.0f/2, -1.0f/2, -1.0f/2,

           -1.0f/2, -1.0f/2, -1.0f/2,
           -1.0f/2, -1.0f/2,  1.0f/2,
            1.0f/2, -1.0f/2,  1.0f/2,

           // top
            1.0f/2,  1.0f/2,  1.0f/2,
           -1.0f/2,  1.0f/2,  1.0f/2,
           -1.0f/2,  1.0f/2, -1.0f/2,

           -1.0f/2,  1.0f/2, -1.0f/2,
            1.0f/2,  1.0f/2, -1.0f/2,
            1.0f/2,  1.0f/2,  1.0f/2
       };

        _generateGeometry(shader, vertices, vertices);
    }

    bool CollisionBox::collisionCheck(const CollisionShape &mesh) {
        if (&mesh == this) { return false; }

        bool collides = CollisionDetector::checkCollision(this, &mesh);
        return collides;
    }

}