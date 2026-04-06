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
        glGenVertexArrays(1, &vao);
        glBindVertexArray(vao);
        GLint positionLoc = glGetAttribLocation(shaderProgram, "position");
        glEnableVertexAttribArray(positionLoc);
        glVertexAttribPointer(positionLoc, 3, GL_FLOAT, GL_FALSE, 0, 0);

        // UNIFORM BINDING
        Mid = glGetUniformLocation(shaderProgram, "model");
        Vid = glGetUniformLocation(shaderProgram, "view");
        Pid = glGetUniformLocation(shaderProgram, "projection");
        PVMid = glGetUniformLocation(shaderProgram, "PVM");
    }

    void Mesh::draw(int WIN_WIDTH, int WIN_HEIGHT) {
        glUseProgram(shaderProgram);
        glBindVertexArray(vao);

        // MODEL MATRIX
        glm::mat4 modelM = glm::mat4(1.0f);

        // VIEW MATRIX
        glm::vec3 eye = glm::vec3(-8.0f, 0.0f, 5.0f);
        glm::vec3 center = glm::vec3(0.0f, 0.0f, 0.0f);
        glm::vec3 up  = glm::vec3(0.0f, 1.0f, 0.0f);
        glm::mat4 viewM = glm::lookAt(eye, center, up);

        // PROJECTION MATRIX
        float fovy = glm::radians(45.0f);
        float aspect = static_cast<float>(WIN_WIDTH) / static_cast<float>(WIN_HEIGHT);
        float nearZ = 0.1f;
        float farZ = 100.0f;
        glm::mat4 projectionM = glm::perspective(fovy, aspect, nearZ, farZ);

        glm::mat4 PVM = projectionM * viewM * modelM;

        // UNIFORM APPLY
        glUniformMatrix4fv(Mid, 1, GL_FALSE, glm::value_ptr(modelM)); // TRUE: M -> M^t, opengl accepts vectors by rows.
        glUniformMatrix4fv(Vid, 1, GL_FALSE, glm::value_ptr(viewM));
        glUniformMatrix4fv(Pid, 1, GL_FALSE, glm::value_ptr(projectionM));
        glUniformMatrix4fv(PVMid, 1, GL_FALSE, glm::value_ptr(PVM));

        // DRAW IT TO THE SCREEN
        glDrawArrays(GL_TRIANGLES, 0, numVertices);
    };
}