#ifndef PGR_SEM_COPAKOND_OBJMESH_H
#define PGR_SEM_COPAKOND_OBJMESH_H

#include "mesh.h"

namespace copakond {
    class ObjMesh : public Mesh {
    private:
        std::string _fileLocation;
        std::vector<float> _vertices;
        std::vector<unsigned int> _faces;

        GLuint _ebo;

        void constructor(const std::string &objFileLocation, bool normalizeCoord);

    public:
        ObjMesh(const std::string &objFileLocation);
        ObjMesh(const std::string &objFileLocation, const glm::vec3 &translation);
        ObjMesh(const std::string &objFileLocation, const glm::vec3 &translation, const glm::vec3 &rotation);
        ObjMesh(const std::string &objFileLocation, const glm::vec3 &translation, const glm::vec3 &rotation, const glm::vec3 &scale);

        ObjMesh(const std::string &objFileLocation, bool normalizeCoord);
        ObjMesh(const std::string &objFileLocation, bool normalizeCoord, const glm::vec3 &translation);
        ObjMesh(const std::string &objFileLocation, bool normalizeCoord, const glm::vec3 &translation, const glm::vec3 &rotation);
        ObjMesh(const std::string &objFileLocation, bool normalizeCoord, const glm::vec3 &translation, const glm::vec3 &rotation,
                const glm::vec3 &scale);

        void init(GLuint shader) override;
        void draw() override;
    };
}

#endif //PGR_SEM_COPAKOND_OBJMESH_H
