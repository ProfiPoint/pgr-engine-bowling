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
        glGenBuffers(1, &arrayBuffer);
        glBindBuffer(GL_ARRAY_BUFFER, arrayBuffer);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

		// VAO
        glGenVertexArrays(1, &vao_unfId);
        glBindVertexArray(vao_unfId);
        GLint positionLoc = glGetAttribLocation(shaderProgram, "position");
        glEnableVertexAttribArray(positionLoc);
        glVertexAttribPointer(positionLoc, 3, GL_FLOAT, GL_FALSE, 0, 0);
    }

    void Mesh::draw(int WIN_WIDTH, int WIN_HEIGHT) {
        glDrawArrays(GL_TRIANGLES, 0, numVertices);
    };
}