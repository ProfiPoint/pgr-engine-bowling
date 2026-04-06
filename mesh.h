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

        GLint M_unfId; // model matrix uniform index;
        GLint V_unfId; // view matrix uniform index;
        GLint P_unfId; // projection matrix uniform index;
        GLint PVM_unfId; // PVM matrix uniform index;

    public:
        Mesh();

        virtual void init(GLuint shader);
        virtual void draw(int WIN_WIDTH, int WIN_HEIGHT);
    };
}

#endif //PGR_SEM_COPAKOND_MESH_H