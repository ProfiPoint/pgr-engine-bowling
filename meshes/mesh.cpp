#include "mesh.h"

namespace copakond {
    Mesh::Mesh() {}

    void Mesh::init(GLuint shader) {
        shaderProgram = shader;

        static const float vertices[] = {
            1.0f, 1.0f/2, 0.0f,
            1.0f, -1.0f, 0.0f,
            -1.0f/2, -1.0f, 0.0f,

            -1.0f, 1.0f, 0.0f,
            1.0f/2, 1.0f, 0.0f,
            -1.0f, -1.0f/2, 0.0f,
        };

        numVertices = sizeof(vertices) / (3 * sizeof(float));

        // VBO
        glGenBuffers(1, &vbo);
        glBindBuffer(GL_ARRAY_BUFFER, vbo);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

		// VAO
        glGenVertexArrays(1, &vao);
        glBindVertexArray(vao);
        GLint position = glGetAttribLocation(shaderProgram, "position");
        glEnableVertexAttribArray(position);
        glVertexAttribPointer(position, 3, GL_FLOAT, GL_FALSE, 0, 0);

        // UNBIND
        glBindVertexArray(0);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
    }

    void Mesh::draw(int WIN_WIDTH, int WIN_HEIGHT) {
        glBindVertexArray(vao);
        glDrawArrays(GL_TRIANGLES, 0, numVertices);
        glBindVertexArray(0);
    };
}