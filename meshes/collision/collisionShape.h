#ifndef PGR_SEM_COPAKOND_COLLISIONSHAPE_H
#define PGR_SEM_COPAKOND_COLLISIONSHAPE_H

#include "../mesh.h"

namespace copakond {
    class CollisionShape : public Mesh {
    protected:
        bool _enabled = true;
        bool _debug = false;

        void _generateGeometry(GLuint shader, const std::vector<float>& vertices, const std::vector<float>& normals);

    public:
        CollisionShape(const glm::vec3 &position = glm::vec3(0.0f), const glm::vec3 &rotation = glm::vec3(0.0f),
            const glm::vec3 &scale = glm::vec3(1.0f), bool debug = false);

        void draw(float deltaTime) override;

        void setDebug(bool debug) { _debug = debug; }
        void enable() { _enabled = true; }
        void disable() { _enabled = false; }
        bool isEnabled() const { return _enabled; }

        virtual bool collisionCheck(const Mesh &mesh) = 0;
    };
}

#endif //PGR_SEM_COPAKOND_COLLISIONSHAPE_H