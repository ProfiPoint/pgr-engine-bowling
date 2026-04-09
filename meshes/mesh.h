#ifndef PGR_SEM_COPAKOND_MESH_H
#define PGR_SEM_COPAKOND_MESH_H

#include "pgr.h"
#include "../geometry/geometry.h"

namespace copakond {
    class Mesh : public Geometry {
    protected:
        GLuint shaderProgram;
        GLuint vbo;
        GLsizei numVertices;

        GLuint vao;

    public:
        Mesh();
        Mesh(const glm::vec3& translation);
        Mesh(const glm::vec3& translation, const glm::vec3& rotation);
        Mesh(const glm::vec3& translation, const glm::vec3& rotation, const glm::vec3& scale);

        virtual void init(GLuint shader);
        virtual void draw();
    };
}

#endif //PGR_SEM_COPAKOND_MESH_H