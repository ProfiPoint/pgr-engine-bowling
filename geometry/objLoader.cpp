#include "objLoader.h"
#include <fstream>
#include <iostream>
#include <string>
#include <sstream>
#include <limits>

// implemented .obj parser from: MIT https://github.com/dartzon/dotObj-parser (the remapBuffers)
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

    ObjLoader::ObjLoader(const std::string& fileName, bool normalizeCoord) {
        if (fileName.length() < 4 || fileName.substr(fileName.length() - 4) != ".obj") {
            std::cerr << "File must be .obj: " << fileName << std::endl;
            exit(1);
        }

        std::ifstream file(fileName);
        if (!file.is_open()) {
            std::cerr << "Error opening file " << fileName << std::endl;
            exit(1);
        }

        std::vector<float> vertices;
        std::vector<float> normals;
        std::vector<std::string> faces;
        std::string line;

        while (std::getline(file, line)) {
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
                faces.push_back(data[1]);
                faces.push_back(data[2]);
                faces.push_back(data[3]);
            }
        }

        if (normalizeCoord) {
            float min[3] = {std::numeric_limits<float>::max(), std::numeric_limits<float>::max(), std::numeric_limits<float>::max()};
            float max[3] = {std::numeric_limits<float>::lowest(), std::numeric_limits<float>::lowest(), std::numeric_limits<float>::lowest()};

            // get the minimum point and maximum point (creating bounding box)
            for (size_t i = 0; i < vertices.size(); i++) {
                float point = vertices[i];
                int modIndex = i % 3;
                if (point > max[modIndex]) { max[modIndex] = point; }
                if (point < min[modIndex]) { min[modIndex] = point; }
            }

            // center of the object
            float center[3] = {
                (max[0] + min[0]) / 2.0f,
                (max[1] + min[1]) / 2.0f,
                (max[2] + min[2]) / 2.0f
            };

            // size of the object
            float size[3] = {
                max[0] - min[0],
                max[1] - min[1],
                max[2] - min[2],
            };

            // scale factor to get it in coord [-1,-1,-1] x [1,1,1]
            float scaleFactor[3];
            for (int i = 0; i < 3; i++) {
                if (size[i] > 0.0f) {
                    scaleFactor[i] = 2.0f / size[i];
                } else {
                    scaleFactor[i] = 1.0f;
                }
            }

            // remap the coord to [-1,-1,-1] x [1,1,1]
            for (size_t i = 0; i < vertices.size(); i++) {
                int modIndex = i % 3;
                vertices[i] = (vertices[i] - center[modIndex]) * scaleFactor[modIndex];
            }
        }

        remapBuffers(vertices, normals, faces);
    }

    // reorders the vertices and normals, so each index has the same data. Implementation of dartzon's obj parser.
    void ObjLoader::remapBuffers(const std::vector<float>& tempV, const std::vector<float>& tempVn, const std::vector<std::string>& rawFaces) {
        std::map<std::string, unsigned int> history;

        for (const std::string& vertexCombo : rawFaces) {
            if (history.count(vertexCombo) > 0) { // already parsed to history
                _faces.push_back(history[vertexCombo]);

            } else { // new - processes
                int vIndex = 0;
                int nIndex = 0;
                if (sscanf(vertexCombo.c_str(), "%d//%d", &vIndex, &nIndex) == 2) { // parses the face string in format vertexX//normalX  (x/y/z)
                    int vBase = (vIndex - 1) * 3;
                    int nBase = (nIndex - 1) * 3;

                    _vertices.push_back(tempV[vBase]);
                    _vertices.push_back(tempV[vBase + 1]);
                    _vertices.push_back(tempV[vBase + 2]);

                    _normals.push_back(tempVn[nBase]);
                    _normals.push_back(tempVn[nBase + 1]);
                    _normals.push_back(tempVn[nBase + 2]);

                    unsigned int newIndex = (_vertices.size() / 3) - 1;
                    history[vertexCombo] = newIndex;
                    _faces.push_back(newIndex);
                }
            }
        }
    }

    const std::vector<float>& ObjLoader::getVertices() const {
        return _vertices;
    }

    const std::vector<float>& ObjLoader::getNormals() const {
        return _normals;
    }

    const std::vector<unsigned int>& ObjLoader::getFaces() const {
        return _faces;
    }
}
