#include "mesh.h"

namespace copakond {
    Mesh::Mesh() : Geometry() {}
    Mesh::Mesh(const glm::vec3& translation) : Geometry(translation) {}
    Mesh::Mesh(const glm::vec3& translation, const glm::vec3& rotation) : Geometry(translation, rotation) {}
    Mesh::Mesh(const glm::vec3& translation, const glm::vec3& rotation, const glm::vec3& scale) : Geometry(translation, rotation, scale) {}

    void Mesh::init(GLuint shader) {
        _shaderProgram = shader;

        static const float vertices[] = {
            1.0f, 1.0f/2, 0.0f,
            1.0f, -1.0f, 0.0f,
            -1.0f/2, -1.0f, 0.0f,

            -1.0f, 1.0f, 0.0f,
            1.0f/2, 1.0f, 0.0f,
            -1.0f, -1.0f/2, 0.0f,
        };

        _numVertices = sizeof(vertices) / (3 * sizeof(float));

        // VBO
        glGenBuffers(1, &_vbo);
        glBindBuffer(GL_ARRAY_BUFFER, _vbo);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

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