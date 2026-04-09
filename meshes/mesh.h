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

        virtual void init(GLuint shader);
        virtual void draw(int WIN_WIDTH, int WIN_HEIGHT);
    };
}

#endif //PGR_SEM_COPAKOND_MESH_H