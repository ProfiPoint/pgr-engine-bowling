#include "objMesh.h"
#include "../geometry/objLoader.h"

namespace copakond {
    void ObjMesh::constructor(const std::string& objFileLocation, bool normalizeCoord) {
        ObjLoader objLoader = ObjLoader(objFileLocation, normalizeCoord);
        vertices = objLoader.getVertices();
        faces = objLoader.getFaces();
        //TODO - IMPLEMENT: normals = objLoader.getNormals();
        numVertices = faces.size();
    }

    ObjMesh::ObjMesh(const std::string& objFileLocation)
    : Mesh(), fileLocation(objFileLocation) { constructor(objFileLocation, false); }
    ObjMesh::ObjMesh(const std::string& objFileLocation, const glm::vec3& translation)
    : Mesh(translation), fileLocation(objFileLocation) { constructor(objFileLocation, false); }
    ObjMesh::ObjMesh(const std::string& objFileLocation, const glm::vec3& translation, const glm::vec3& rotation)
    : Mesh(translation, rotation), fileLocation(objFileLocation) { constructor(objFileLocation, false); }
    ObjMesh::ObjMesh(const std::string& objFileLocation, const glm::vec3& translation, const glm::vec3& rotation, const glm::vec3& scale)
    : Mesh(translation, rotation, scale), fileLocation(objFileLocation) { constructor(objFileLocation, false); }

    ObjMesh::ObjMesh(const std::string& objFileLocation, bool normalizeCoord)
    : Mesh(), fileLocation(objFileLocation) { constructor(objFileLocation, normalizeCoord); }
    ObjMesh::ObjMesh(const std::string& objFileLocation, bool normalizeCoord, const glm::vec3& translation)
    : Mesh(translation), fileLocation(objFileLocation) { constructor(objFileLocation, normalizeCoord); }
    ObjMesh::ObjMesh(const std::string& objFileLocation, bool normalizeCoord, const glm::vec3& translation, const glm::vec3& rotation)
    : Mesh(translation, rotation), fileLocation(objFileLocation) { constructor(objFileLocation, normalizeCoord); }
    ObjMesh::ObjMesh(const std::string& objFileLocation, bool normalizeCoord, const glm::vec3& translation, const glm::vec3& rotation, const glm::vec3& scale)
    : Mesh(translation, rotation, scale), fileLocation(objFileLocation) { constructor(objFileLocation, normalizeCoord); }

    void ObjMesh::init(GLuint shader) {
        shaderProgram = shader;

        //BINDING
        glGenVertexArrays(1, &vao);
        glBindVertexArray(vao);
        glGenBuffers(1, &vbo);
        glGenBuffers(1, &ebo);

        // VBO
        glBindBuffer(GL_ARRAY_BUFFER, vbo);
        glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), vertices.data(), GL_STATIC_DRAW);

        // VAO
        GLint position = glGetAttribLocation(shaderProgram, "position");
        glEnableVertexAttribArray(position);
        glVertexAttribPointer(position, 3, GL_FLOAT, GL_FALSE, 0, 0);

        // EBO
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, faces.size() * sizeof(unsigned int), faces.data(), GL_STATIC_DRAW);

        // UNBIND
        glBindVertexArray(0);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
    }

    void ObjMesh::draw(int WIN_WIDTH, int WIN_HEIGHT) {
        glBindVertexArray(vao);
        glDrawElements(GL_TRIANGLES, numVertices, GL_UNSIGNED_INT, 0);
        glBindVertexArray(0);
    };
}