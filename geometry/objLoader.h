#ifndef PGR_SEM_COPAKOND_OBJLOADER_H
#define PGR_SEM_COPAKOND_OBJLOADER_H
#include <string>
#include <vector>

#include <map> // Added for our history tracker

namespace copakond {
    class ObjLoader {
    private:
        std::vector<float> vertices;
        std::vector<float> normals;
        std::vector<unsigned int> faces;

        void remapBuffers(const std::vector<float>& vertices, const std::vector<float>& normals, const std::vector<std::string>& faces);

    public:
        ObjLoader(const std::string& fileName, bool normalizeCoord);

        const std::vector<float>& getVertices() const;
        const std::vector<float>& getNormals() const;
        const std::vector<unsigned int>& getFaces() const;
    };
}

#endif //PGR_SEM_COPAKOND_OBJLOADER_H