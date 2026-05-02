#ifndef PGR_SEM_COPAKOND_OBJLOADER_H
#define PGR_SEM_COPAKOND_OBJLOADER_H

#include "../geometry/material.h"
#include "../meshes/mesh.h"

#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include <string>
#include <sstream>
#include <limits>
#include <map>

namespace copakond {
    class ObjLoader {
    private:
        std::vector<float> _vertices;
        std::vector<float> _normals;
        std::vector<float> _uvs;
        std::vector<unsigned int> _faces;
        std::map<std::string, std::shared_ptr<Material>> _materialDict;
        std::vector<SubMesh> _subMeshes;

        void remapBuffers(const std::vector<float> &vertices, const std::vector<float> &normals, const std::vector<float> &tempUvs, const
            std::vector<std::string> &faces);

    public:
        ObjLoader(const std::string &fileName, bool normalizeCoord);

        static std::vector<std::string> splitString(const std::string &str);



        const std::vector<SubMesh>& getSubMeshes() const { return _subMeshes; }
        const std::vector<float> &getVertices() const { return _vertices; }
        const std::vector<float> &getNormals() const { return _normals; }
        const std::vector<float>& getUvs() const { return _uvs; }
        const std::vector<unsigned int> &getFaces() const { return _faces; }
    };
}

#endif //PGR_SEM_COPAKOND_OBJLOADER_H
