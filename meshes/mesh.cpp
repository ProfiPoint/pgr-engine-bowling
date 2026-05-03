#include "mesh.h"

#include <iostream>

namespace copakond {
    int Mesh::globalMeshCounter = 0;

    void Mesh::_SetId() {
        id = globalMeshCounter++;
    }

    Mesh::Mesh() : Geometry() { _SetId(); }

    Mesh::Mesh(const glm::vec3 &position) : Geometry(position) { _SetId(); }

    Mesh::Mesh(const glm::vec3 &position, const glm::vec3 &rotation) : Geometry(position, rotation) { _SetId(); }

    Mesh::Mesh(const glm::vec3 &position, const glm::vec3 &rotation, const glm::vec3 &scale) : Geometry(position, rotation, scale) { _SetId(); }

    void Mesh::setVertices(const std::vector<float> &vertices) {
        _vertices = vertices;
    }

    void Mesh::setMaterial(const std::shared_ptr<Material> &material) {
        _material = material;
        for (auto& subMesh : _subMeshes) {
            subMesh.material = material;
        }
    }
    std::shared_ptr<Material> Mesh::getMaterial() {
        return _material;
    }

    void Mesh::init(GLuint shader) {
        _shaderProgram = shader;

        std::vector<float> vertices = {
            -1.0f / 2, -1.0f, 0.0f,
            1.0f, -1.0f, 0.0f,
            1.0f, 1.0f / 2, 0.0f,

            -1.0f, -1.0f / 2, 0.0f,
            1.0f / 2, 1.0f, 0.0f,
            -1.0f, 1.0f, 0.0f,
        };

        if (!_vertices.empty()) {
            vertices = _vertices;
        }

        _numVertices = vertices.size() / 3;

        // VBO
        glGenBuffers(1, &_vboVertices);
        glBindBuffer(GL_ARRAY_BUFFER, _vboVertices);
        glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), vertices.data(), GL_STATIC_DRAW);

        // VAO
        glGenVertexArrays(1, &_vao);
        glBindVertexArray(_vao);
        GLint position = glGetAttribLocation(_shaderProgram, "position");
        glEnableVertexAttribArray(position);
        glVertexAttribPointer(position, 3, GL_FLOAT, GL_FALSE, 0, 0);

        // UNBIND
        glBindVertexArray(0);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
    }

    void Mesh::draw() {
        glBindVertexArray(_vao);
        glDrawArrays(GL_TRIANGLES, 0, _numVertices);
        glBindVertexArray(0);
    };
}
