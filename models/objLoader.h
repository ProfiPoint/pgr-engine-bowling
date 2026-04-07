#ifndef PGR_SEM_COPAKOND_OBJLOADER_H
#define PGR_SEM_COPAKOND_OBJLOADER_H
#include <string>
#include <vector>

namespace copakond {
    class ObjLoader {
    private:
        std::vector<float> vertices;
        std::vector<int> faces;
        std::vector<float> normals;
    public:
        ObjLoader(const std::string& fileName);

        std::vector<float> getVertices();
        std::vector<int> getFaces();
        std::vector<float> getNormals();
    };
}

#endif //PGR_SEM_COPAKOND_OBJLOADER_H