#include "objLoader.h"
#include <fstream>
#include <iostream>
#include <string>
#include <sstream>

namespace copakond {
    std::vector<std::string> splitString(const std::string& str) { // https://stackoverflow.com/questions/5167625
        std::vector<std::string> tokens;
        std::stringstream ss(str);
        std::string token;
        while (ss >> token) {
            tokens.push_back(token);
        }
        return tokens;
    }

    ObjLoader::ObjLoader(const std::string& fileName) {
        if (fileName.length() < 4 || fileName.substr(fileName.length() - 4) != ".obj") {
            std::cerr << "File must be .obj: " << fileName << std::endl;
            exit(1);
        }

        std::ifstream file(fileName);
        if (file.is_open()) {
            std::string line;
            while (std::getline(file, line))
            {
                std::vector<std::string> data = splitString(line);
                if (data.empty()) continue;

                if (data[0] == "v" && data.size() >= 4) {
                    vertices.push_back(std::stof(data[1]));
                    vertices.push_back(std::stof(data[2]));
                    vertices.push_back(std::stof(data[3]));
                }
                else if (data[0] == "vn" && data.size() >= 4) {
                    normals.push_back(std::stof(data[1]));
                    normals.push_back(std::stof(data[2]));
                    normals.push_back(std::stof(data[3]));
                }
                else if (data[0] == "f" && data.size() >= 4) {
                    faces.push_back(std::stoi(data[1]) - 1);
                    faces.push_back(std::stoi(data[2]) - 1);
                    faces.push_back(std::stoi(data[3]) - 1);
                }
            }
        } else {
            std::cerr << "Error opening file " << fileName << std::endl;
            exit(1);
        }
    }

    std::vector<float> ObjLoader::getVertices() {
        return vertices;
    }

    std::vector<int> ObjLoader::getFaces() {
        return faces;
    }
}
