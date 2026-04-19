#include "objMesh.h"
#include "../utils/objLoader.h"

namespace copakond {
    void ObjMesh::constructor(const std::string &objFileLocation, bool normalizeCoord) {
        ObjLoader objLoader = ObjLoader(objFileLocation, normalizeCoord);
        _vertices = objLoader.getVertices();
        _faces = objLoader.getFaces();
        _normals = objLoader.getNormals();
        _numVertices = _faces.size();

        setMaterial(objLoader.getMaterial());
    }

    ObjMesh::ObjMesh(const std::string &objFileLocation)
        : Mesh(), _fileLocation(objFileLocation) { constructor(objFileLocation, false); }

    ObjMesh::ObjMesh(const std::string &objFileLocation, const glm::vec3 &translation)
        : Mesh(translation), _fileLocation(objFileLocation) { constructor(objFileLocation, false); }

    ObjMesh::ObjMesh(const std::string &objFileLocation, const glm::vec3 &translation, const glm::vec3 &rotation)
        : Mesh(translation, rotation), _fileLocation(objFileLocation) { constructor(objFileLocation, false); }

    ObjMesh::ObjMesh(const std::string &objFileLocation, const glm::vec3 &translation, const glm::vec3 &rotation, const glm::vec3 &scale)
        : Mesh(translation, rotation, scale), _fileLocation(objFileLocation) { constructor(objFileLocation, false); }

    ObjMesh::ObjMesh(const std::string &objFileLocation, bool normalizeCoord)
        : Mesh(), _fileLocation(objFileLocation) { constructor(objFileLocation, normalizeCoord); }

    ObjMesh::ObjMesh(const std::string &objFileLocation, bool normalizeCoord, const glm::vec3 &translation)
        : Mesh(translation), _fileLocation(objFileLocation) { constructor(objFileLocation, normalizeCoord); }

    ObjMesh::ObjMesh(const std::string &objFileLocation, bool normalizeCoord, const glm::vec3 &translation, const glm::vec3 &rotation)
        : Mesh(translation, rotation), _fileLocation(objFileLocation) { constructor(objFileLocation, normalizeCoord); }

    ObjMesh::ObjMesh(const std::string &objFileLocation, bool normalizeCoord, const glm::vec3 &translation, const glm::vec3 &rotation,
                     const glm::vec3 &scale)
        : Mesh(translation, rotation, scale), _fileLocation(objFileLocation) { constructor(objFileLocation, normalizeCoord); }

    void ObjMesh::init(GLuint shader) {
        _shaderProgram = shader;

        //BINDING VAO
        glGenVertexArrays(1, &_vao);
        glBindVertexArray(_vao);
        glGenBuffers(1, &_vboVertices);
        glGenBuffers(1, &_vboNormals);
        glGenBuffers(1, &_ebo);

        // VERTICES
        glBindBuffer(GL_ARRAY_BUFFER, _vboVertices); // VBO
        glBufferData(GL_ARRAY_BUFFER, _vertices.size() * sizeof(float), _vertices.data(), GL_STATIC_DRAW);

        GLint position = glGetAttribLocation(_shaderProgram, "position"); // VAO
        glEnableVertexAttribArray(position);
        glVertexAttribPointer(position, 3, GL_FLOAT, GL_FALSE, 0, nullptr);


        // NORMALS
        glBindBuffer(GL_ARRAY_BUFFER, _vboNormals); // VBO
        glBufferData(GL_ARRAY_BUFFER, _normals.size() * sizeof(float), _normals.data(), GL_STATIC_DRAW);

        GLint normal = glGetAttribLocation(_shaderProgram, "normal"); // VAO
        glEnableVertexAttribArray(normal);
        glVertexAttribPointer(normal, 3, GL_FLOAT, GL_TRUE, 0, nullptr); // GL_TRUE normalize normals


        // EBO
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _ebo);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, _faces.size() * sizeof(unsigned int), _faces.data(), GL_STATIC_DRAW);

        // UNBIND
        glBindVertexArray(0);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
    }

    void ObjMesh::draw() {
        glBindVertexArray(_vao);
        glDrawElements(GL_TRIANGLES, _numVertices, GL_UNSIGNED_INT, nullptr);
        glBindVertexArray(0);
    };
}
