#include "mtlLoader.h"
#include "objLoader.h"

#include <fstream>
#include "../shaders/shader.h"

namespace copakond {
    MtlLoader::MtlLoader(std::string fileName) {
        if (fileName.length() < 4 || fileName.substr(fileName.length() - 4) != ".mtl") {
            return;
        }

        std::ifstream file(fileName);
        if (!file.is_open()) {
            return;
        }

        std::string basePath = "";
        size_t pos = fileName.find_last_of("\\/");
        if (pos != std::string::npos) {
            basePath = fileName.substr(0, pos + 1);
        }

        std::cout << "loaded .MTL file: " << fileName << std::endl;

        std::string line;
        std::shared_ptr<Material> curMaterial = nullptr;

        while (std::getline(file, line)) {
            std::vector<std::string> data = ObjLoader::splitString(line);
            if (data.empty()) continue;

            if (data[0] == "newmtl") {
                curMaterial = std::make_shared<Material>();
                _materials[data[1]] = curMaterial;
            }

            else if (data[0] == "Ka") {
                /*   ignoring ambient using 1/4 of diffuse
                _material->ambient() = glm::vec3(std::stof(data[1]), std::stof(data[2]), std::stof(data[3])); */
            }
            else if (data[0] == "Kd") {
                curMaterial->diffuse() = glm::vec3(std::stof(data[1]), std::stof(data[2]), std::stof(data[3]));
                curMaterial->ambient() = glm::vec3(std::stof(data[1]), std::stof(data[2]), std::stof(data[3])) * Shader::getWorldAmbient();
            }
            else if (data[0] == "Ks") {
                curMaterial->specular() = glm::vec3(std::stof(data[1]), std::stof(data[2]), std::stof(data[3]));
            }
            else if (data[0] == "Ns") {
                curMaterial->shininess() = std::stof(data[1]);
            }
            else if (data[0] == "d") {
                curMaterial->alpha() = std::stof(data[1]);
            }
            else if (data[0] == "Tr") {
                curMaterial->alpha() = 1.0f - std::stof(data[1]);
            }

            else if (data[0] == "map_Kd") {
                curMaterial->setDiffuseTexture(basePath + data[1]);
            }
            else if (data[0] == "map_Ks") {
                curMaterial->setSpecularTexture(basePath + data[1]);
            }
            else if (data[0] == "map_Ns") {
                curMaterial->setShininessTexture(basePath + data[1]);
            }
            else if (data[0] == "map_d") {
                curMaterial->setAlphaTexture(basePath + data[1]);
            }
            else if (data[0] == "map_Bump") {
                curMaterial->setNormalTexture(basePath + data[1]);
                std::cerr << "Bump map not implemented" << fileName << std::endl;
            }
            else if (data[0] == "bump") {
                curMaterial->setNormalTexture(basePath + data[1]);
                std::cerr << "Bump map not implemented" << fileName << std::endl;
            }
        }

    }
}
