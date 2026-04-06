#ifndef PGR_SEM_COPAKOND_MESH_H
#define PGR_SEM_COPAKOND_MESH_H

#include "pgr.h"

namespace copakond {
    class Mesh {
    protected:
        GLuint shaderProgram;
        GLuint arrayBuffer;
        GLuint vao;
        GLsizei numVertices;

        GLint Mid; // model matrix uniform index;
        GLint Vid; // view matrix uniform index;
        GLint Pid; // projection matrix uniform index;
        GLint PVMid; // PVM matrix uniform index;

    public:
        Mesh();

        virtual void init(GLuint shader);
        virtual void draw(int WIN_WIDTH, int WIN_HEIGHT);
    };
}

#endif //PGR_SEM_COPAKOND_MESH_H