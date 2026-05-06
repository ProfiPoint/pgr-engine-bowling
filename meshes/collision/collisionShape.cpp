#include "collisionShape.h"

namespace copakond {
    CollisionShape::CollisionShape(const glm::vec3 &position, const glm::vec3 &rotation, const glm::vec3 &scale, bool visible)
        : Mesh(position, rotation, scale) {

        setVisible(visible);

        _material = std::make_shared<Material>();
        if (visible) {
            _material->ambient() = glm::vec3(0.19f, 0.36f, 0.86f);
            _material->diffuse() = glm::vec3(0.19f, 0.36f, 0.86f);
            _material->specular() = glm::vec3(0.0f, 0.0f, 0.0f);
            _material->alpha() = 0.25f;
        } else {
            _material->specular() = glm::vec3(0.0f, 0.0f, 0.0f);
            _material->alpha() = 0.0f;
        }
    }

    void CollisionShape::draw(float deltaTime) {
        if (!_visible) { return; }
        Mesh::draw(deltaTime);
    }

    void CollisionShape::_generateGeometry(GLuint shader, const std::vector<float>& vertices, const std::vector<float>& normals) {
        _shaderProgram = shader;
        _numVertices = vertices.size() / 3;

        //BINDING VAO
        glGenVertexArrays(1, &_vao);
        glBindVertexArray(_vao);

        // VERTICES
        glGenBuffers(1, &_vboVertices);
        glBindBuffer(GL_ARRAY_BUFFER, _vboVertices);
        glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), vertices.data(), GL_STATIC_DRAW);
        GLint posAttrib = glGetAttribLocation(_shaderProgram, "position");
        glEnableVertexAttribArray(posAttrib);
        glVertexAttribPointer(posAttrib, 3, GL_FLOAT, GL_FALSE, 0, 0);

        // NORMALS
        if (!normals.empty()) {
            glGenBuffers(1, &_vboNormals);
            glBindBuffer(GL_ARRAY_BUFFER, _vboNormals);
            glBufferData(GL_ARRAY_BUFFER, normals.size() * sizeof(float), normals.data(), GL_STATIC_DRAW);
            GLint normAttrib = glGetAttribLocation(_shaderProgram, "normal");
            glEnableVertexAttribArray(normAttrib);
            glVertexAttribPointer(normAttrib, 3, GL_FLOAT, GL_FALSE, 0, 0);
        }

        // UNBIND
        glBindVertexArray(0);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
    }
}
