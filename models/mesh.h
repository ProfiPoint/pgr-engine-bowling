#ifndef PGR_SEM_COPAKOND_MESH_H
#define PGR_SEM_COPAKOND_MESH_H

#include "pgr.h"

namespace copakond {
    class Mesh {
    protected:
        GLuint shaderProgram;
        GLuint arrayBuffer;
        GLsizei numVertices;

        GLuint vao_unfId;

    public:
        Mesh();

        virtual void init(GLuint shader);
        virtual void draw(int WIN_WIDTH, int WIN_HEIGHT);
    };
}

#endif //PGR_SEM_COPAKOND_MESH_H