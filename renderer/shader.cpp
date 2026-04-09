#include "shader.h"

namespace copakond {
    Shader::Shader() {}

    GLuint Shader::init(std::string vertShaderLocation, std::string fragShaderLocation) {
        GLuint shaders[] = {
            pgr::createShaderFromFile(GL_VERTEX_SHADER, vertShaderLocation),
            pgr::createShaderFromFile(GL_FRAGMENT_SHADER, fragShaderLocation),
            0
        };

        shaderProgram = pgr::createProgram(shaders);

        // UNIFORM BINDING
        modelUID = glGetUniformLocation(shaderProgram, "model");
        viewUID = glGetUniformLocation(shaderProgram, "view");
        projectionUID = glGetUniformLocation(shaderProgram, "projection");
        pvmUID = glGetUniformLocation(shaderProgram, "PVM");
        return shaderProgram;
    }

    void Shader::update(Camera &camera, int WIN_WIDTH, int WIN_HEIGHT) {
        glUseProgram(shaderProgram);
        viewM = camera.getViewMatrix();
        projectionM = camera.getProjectionMatrix(WIN_WIDTH, WIN_HEIGHT);

        // UNIFORM APPLY
        glUniformMatrix4fv(viewUID, 1, GL_FALSE, glm::value_ptr(viewM));
        glUniformMatrix4fv(projectionUID, 1, GL_FALSE, glm::value_ptr(projectionM));
    }

    void Shader::draw(Mesh &mesh) {
        glm::mat4 modelM = mesh.getModelMatrix();
        glm::mat4 PVM = projectionM * viewM * modelM;

        // UNIFORM APPLY
        glUniformMatrix4fv(modelUID, 1, GL_FALSE, glm::value_ptr(modelM)); // TRUE: M -> M^t, opengl accepts vectors by rows.
        glUniformMatrix4fv(pvmUID, 1, GL_FALSE, glm::value_ptr(PVM));
        mesh.draw();
    };
}