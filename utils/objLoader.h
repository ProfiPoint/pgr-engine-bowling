#ifndef PGR_SEM_COPAKOND_OBJLOADER_H
#define PGR_SEM_COPAKOND_OBJLOADER_H

#include "../geometry/material.h"

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
        std::shared_ptr<Material> _material = std::make_shared<Material>();

        void remapBuffers(const std::vector<float> &vertices, const std::vector<float> &normals, const std::vector<float> &tempUvs, const
            std::vector<std::string> &faces);

    public:
        ObjLoader(const std::string &fileName, bool normalizeCoord);

        static std::shared_ptr<Material> ObjLoader::loadMtl(std::string fileName);
        static std::vector<std::string> ObjLoader::splitString(const std::string &str);

        std::shared_ptr<Material> getMaterial() const { return _material; }
        const std::vector<float> &ObjLoader::getVertices() const { return _vertices; }
        const std::vector<float> &ObjLoader::getNormals() const { return _normals; }
        const std::vector<float>& getUvs() const { return _uvs; }
        const std::vector<unsigned int> &ObjLoader::getFaces() const { return _faces; }
    };
}

#endif //PGR_SEM_COPAKOND_OBJLOADER_H
