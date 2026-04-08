#ifndef PGR_SEM_COPAKOND_OBJMESH_H
#define PGR_SEM_COPAKOND_OBJMESH_H

#include "mesh.h"

namespace copakond {
    class ObjMesh : public Mesh {
    private:
        std::string fileLocation;
        std::vector<float> vertices;
        std::vector<unsigned int> faces;

        GLuint ebo;

    public:
        ObjMesh(const std::string& objFileLocation, bool normalizeCoord = false);

        void init(GLuint shader) override;
        void draw(int WIN_WIDTH, int WIN_HEIGHT) override;
    };
}

#endif //PGR_SEM_COPAKOND_OBJMESH_H