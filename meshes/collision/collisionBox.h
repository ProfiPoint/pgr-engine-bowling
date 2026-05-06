#ifndef PGR_SEM_COPAKOND_COLLISIONBOX_H
#define PGR_SEM_COPAKOND_COLLISIONBOX_H
#include "../mesh.h"

namespace copakond {
    class CollisionBox : public Mesh {
    protected:
        bool _enabled = true;
        bool _debug = false;

    public:
        CollisionBox(const glm::vec3 &position = glm::vec3(0.0f), const glm::vec3 &rotation = glm::vec3(0.0f),
            const glm::vec3 &scale = glm::vec3(1.0f), bool debug = false);

        void init(GLuint shader) override;
        void draw(float deltaTime) override;

        void enable() { _enabled = true; }
        void disable() { _enabled = false; }
        bool isEnabled() const { return _enabled; }

        bool collisionCheck(Mesh mesh);
    };
}
#endif //PGR_SEM_COPAKOND_COLLISIONBOX_H
