#include "objLoader.h"
#include "mtlLoader.h"

// implemented .obj parser from: MIT https://github.com/dartzon/dotObj-parser (the remapBuffers)
namespace copakond {
    static std::string getBasePath(const std::string& filepath) {
        size_t pos = filepath.find_last_of("\\/");
        if (pos == std::string::npos) {
            return "";
        }
        return filepath.substr(0, pos + 1);
    }

    std::vector<std::string> ObjLoader::splitString(const std::string &str) {
        // https://stackoverflow.com/questions/5167625
        std::vector<std::string> tokens;
        std::stringstream ss(str);
        std::string token;
        while (ss >> token) {
            tokens.push_back(token);
        }
        return tokens;
    }

    ObjLoader::ObjLoader(const std::string &fileName, bool normalizeCoord) {
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
        std::vector<float> uvs;
        std::vector<std::string> faces;
        std::string line;

        while (std::getline(file, line)) {
            std::vector<std::string> data = splitString(line);
            if (data.empty()) continue;

            if (data[0] == "v" && data.size() >= 4) {
                vertices.push_back(std::stof(data[1]));
                vertices.push_back(std::stof(data[2]));
                vertices.push_back(std::stof(data[3]));
            } else if (data[0] == "vn" && data.size() >= 4) {
                normals.push_back(std::stof(data[1]));
                normals.push_back(std::stof(data[2]));
                normals.push_back(std::stof(data[3]));
            } else if (data[0] == "vt") {
                uvs.push_back(std::stof(data[1]));
                uvs.push_back(std::stof(data[2]));
            } else if (data[0] == "f" && data.size() >= 4) {
                faces.push_back(data[1]);
                faces.push_back(data[2]);
                faces.push_back(data[3]);
            } else if (data[0] == "mtllib") {
                std::string basePath = getBasePath(fileName);
                std::string mtlPath = basePath + data[1];
                MtlLoader mtlLoader(mtlPath); // load all of the materials
                _materialDict = mtlLoader.getMaterials();
            } else if (data[0] == "usemtl") {
                // first material
                if (!_subMeshes.empty()) {
                    _subMeshes.back().indexCount = faces.size() - _subMeshes.back().indexOffset;
                }

                SubMesh sm; // create the submesh with the givem material
                sm.material = _materialDict[data[1]];

                // save the count and offset
                sm.indexOffset = faces.size();
                sm.indexCount = 0;
                _subMeshes.push_back(sm);
            }
        }

        // save the offset of the last submesh
        if (!_subMeshes.empty()) {
            _subMeshes.back().indexCount = faces.size() - _subMeshes.back().indexOffset;
        }

        std::cout << "loaded .OBJ file: " << fileName << std::endl;

        if (normalizeCoord) {
            float min[3] = {std::numeric_limits<float>::max(), std::numeric_limits<float>::max(), std::numeric_limits<float>::max()};
            float max[3] = {
                std::numeric_limits<float>::lowest(), std::numeric_limits<float>::lowest(), std::numeric_limits<float>::lowest()
            };

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

            // scale factor to get it in coord [-0.5,-0.5,-0.5] x [0.5,0.5,0.5]
            float scaleFactor[3];
            for (int i = 0; i < 3; i++) {
                if (size[i] > 0.0f) {
                    scaleFactor[i] = 1.0f / size[i];
                } else {
                    scaleFactor[i] = 0.5f;
                }
            }

            // remap the coord to [-1,-1,-1] x [1,1,1]
            for (size_t i = 0; i < vertices.size(); i++) {
                int modIndex = i % 3;
                vertices[i] = (vertices[i] - center[modIndex]) * scaleFactor[modIndex];
            }
        }

        remapBuffers(vertices, normals, uvs, faces);
    }

    // reorders the vertices and normals, so each index has the same data. Implementation of dartzon's obj parser.
    void ObjLoader::remapBuffers(const std::vector<float> &tempV, const std::vector<float> &tempVn, const std::vector<float> &tempUvs,
                                 const std::vector<std::string> &rawFaces) {
        std::map<std::string, unsigned int> history;

        for (const std::string &vertexCombo: rawFaces) {
            if (history.count(vertexCombo) > 0) {
                // already parsed to history
                _faces.push_back(history[vertexCombo]);
            } else {
                // new - processes
                int vIndex = 0;
                int uIndex = 0;
                int nIndex = 0;
                if (sscanf(vertexCombo.c_str(), "%d/%d/%d", &vIndex, &uIndex, &nIndex) == 3) {
                    int vBase = (vIndex - 1) * 3;
                    int uBase = (uIndex - 1) * 2;
                    int nBase = (nIndex - 1) * 3;

                    _vertices.push_back(tempV[vBase]);
                    _vertices.push_back(tempV[vBase + 1]);
                    _vertices.push_back(tempV[vBase + 2]);

                    _normals.push_back(tempVn[nBase]);
                    _normals.push_back(tempVn[nBase + 1]);
                    _normals.push_back(tempVn[nBase + 2]);

                    _uvs.push_back(tempUvs[uBase]);
                    _uvs.push_back(tempUvs[uBase + 1]);

                    unsigned int newIndex = (_vertices.size() / 3) - 1;
                    history[vertexCombo] = newIndex;
                    _faces.push_back(newIndex);
                }
                else if (sscanf(vertexCombo.c_str(), "%d//%d", &vIndex, &nIndex) == 2) {
                    // parses the face string in format vertexX//normalX  (x/y/z)
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
}
