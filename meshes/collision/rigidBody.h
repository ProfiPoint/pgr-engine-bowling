#ifndef PGR_SEM_COPAKOND_RIGIDBODY_H
#define PGR_SEM_COPAKOND_RIGIDBODY_H
#include "collisionBox.h"

namespace copakond {
    class RigidBody : public CollisionBox {
    private:
        float _gravity;
        glm::vec3 _velocity = glm::vec3(0.0f, 0.0f, 0.0f);

    public:
        RigidBody(const glm::vec3 &position = glm::vec3(0.0f), const glm::vec3 &rotation = glm::vec3(0.0f),
            const glm::vec3 &scale = glm::vec3(1.0f), float gravity = 1.0f, bool debug = false);

        //void init(GLuint shader) override;
        void draw(float deltaTime) override;

        //void enable() { _enabled = true; }
        //void disable() { _enabled = false; }
        //bool isEnabled() const { return _enabled; }

        //bool collisionCheck(Mesh mesh);
    };
}

#endif //PGR_SEM_COPAKOND_RIGIDBODY_H
