#include "mtlLoader.h"
#include "objLoader.h"

#include <fstream>

namespace copakond {
    MtlLoader::MtlLoader(std::string fileName) {
        if (fileName.length() < 4 || fileName.substr(fileName.length() - 4) != ".mtl") {
            _material = nullptr;
            return;
        }

        std::ifstream file(fileName);
        if (!file.is_open()) {
            _material = nullptr;
            return;
        }

        std::string line;
        int newmtl_count = 0;

        while (std::getline(file, line)) {
            std::vector<std::string> data = ObjLoader::splitString(line);
            if (data.empty()) continue;

            if (data[0] == "newmtl") {
                if (newmtl_count == 1) {
                    std::cerr << "NOT IMPLEMENTED - Only one material works per .obj -> may produce weird results " << fileName <<
                        std::endl;
                    //exit(0);
                }
                newmtl_count++;
            }

            else if (data[0] == "Ka") {
                /*   ignoring ambient using 1/4 of diffuse
                _material->ambient() = glm::vec3(std::stof(data[1]), std::stof(data[2]), std::stof(data[3])); */
            }
            else if (data[0] == "Kd") {
                _material->diffuse() = glm::vec3(std::stof(data[1]), std::stof(data[2]), std::stof(data[3]));
                _material->ambient() = glm::vec3(std::stof(data[1]), std::stof(data[2]), std::stof(data[3])) * 0.25f; // ambient is 1/4 of diffuse
            }
            else if (data[0] == "Ks") {
                _material->specular() = glm::vec3(std::stof(data[1]), std::stof(data[2]), std::stof(data[3]));
            }
            else if (data[0] == "Ns") {
                _material->shininess() = std::stof(data[1]);
            }
            else if (data[0] == "d") {
                _material->alpha() = std::stof(data[1]);
            }
            else if (data[0] == "Tr") {
                _material->alpha() = 1.0f - std::stof(data[1]);
            }

            else if (data[0] == "map_Kd") {
                _material->setDiffuseTexture(data[1]);
            }
            else if (data[0] == "map_Ks") {
                _material->setSpecularTexture(data[1]);
            }
            else if (data[0] == "map_Ns") {
                _material->setShininessTexture(data[1]);
            }
            else if (data[0] == "map_d") {
                _material->setAlphaTexture(data[1]);
            }
            else if (data[0] == "map_Bump") {
                _material->setNormalTexture(data[1]);
            }
            else if (data[0] == "bump") {
                _material->setNormalTexture(data[1]);
            }
        }

    }
}
