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
        std::vector<unsigned int> _faces;
        std::shared_ptr<Material> _material = std::make_shared<Material>();

        void remapBuffers(const std::vector<float> &vertices, const std::vector<float> &normals, const std::vector<std::string> &faces);

    public:
        ObjLoader(const std::string &fileName, bool normalizeCoord);

        static std::shared_ptr<Material> ObjLoader::loadMtl(std::string fileName);
        static std::vector<std::string> ObjLoader::splitString(const std::string &str);

        std::shared_ptr<Material> getMaterial() const { return _material; }
        const std::vector<float> &getVertices() const;
        const std::vector<float> &getNormals() const;
        const std::vector<unsigned int> &getFaces() const;
    };
}

#endif //PGR_SEM_COPAKOND_OBJLOADER_H
