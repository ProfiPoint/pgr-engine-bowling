#include "objMesh.h"
#include "../geometry/objLoader.h"

namespace copakond {
    ObjMesh::ObjMesh(const std::string& objFileLocation) : Mesh(), fileLocation(objFileLocation)
    {
        ObjLoader objLoader = ObjLoader(objFileLocation);
        vertices = objLoader.getVertices();
        faces = objLoader.getFaces();
        //TODO - IMPLEMENT: normals = objLoader.getNormals();

        numVertices = faces.size();
    }

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