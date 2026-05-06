#ifndef PGR_SEM_COPAKOND_OBJMESH_H
#define PGR_SEM_COPAKOND_OBJMESH_H

#include "../mesh.h"

namespace copakond {
    class ObjMesh : public Mesh {
    private:
        std::string _fileLocation;
        std::vector<float> _vertices;
        std::vector<unsigned int> _faces;
        std::vector<float> _normals;
        std::vector<float> _uvs;

        GLuint _vboUvs = 0;
        GLuint _ebo = 0;

        void constructor(const std::string &objFileLocation, bool normalizeCoord);

    public:
        ObjMesh(const std::string &objFileLocation);
        ObjMesh(const std::string &objFileLocation, const glm::vec3 &position);
        ObjMesh(const std::string &objFileLocation, const glm::vec3 &position, const glm::vec3 &rotation);
        ObjMesh(const std::string &objFileLocation, const glm::vec3 &position, const glm::vec3 &rotation, const glm::vec3 &scale);

        ObjMesh(const std::string &objFileLocation, bool normalizeCoord);
        ObjMesh(const std::string &objFileLocation, bool normalizeCoord, const glm::vec3 &position);
        ObjMesh(const std::string &objFileLocation, bool normalizeCoord, const glm::vec3 &position, const glm::vec3 &rotation);
        ObjMesh(const std::string &objFileLocation, bool normalizeCoord, const glm::vec3 &position, const glm::vec3 &rotation,
                const glm::vec3 &scale);

        ~ObjMesh() override;

        void init(GLuint shader) override;
        void draw(float deltaTime) override;
    };
}

#endif //PGR_SEM_COPAKOND_OBJMESH_H
