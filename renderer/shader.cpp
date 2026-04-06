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

    void Shader::draw(Camera &camera, int WIN_WIDTH, int WIN_HEIGHT) {
        glUseProgram(shaderProgram);

        // TODO: CHANGE THIS: USING DEFAILT MODEL MATRIX
        glm::mat4 modelM = glm::mat4(1.0f);
        glm::mat4 viewM = camera.getViewMatrix();
        glm::mat4 projectionM = camera.getProjectionMatrix(WIN_WIDTH, WIN_HEIGHT);
        glm::mat4 PVM = projectionM * viewM * modelM;

        // UNIFORM APPLY
        glUniformMatrix4fv(modelUID, 1, GL_FALSE, glm::value_ptr(modelM)); // TRUE: M -> M^t, opengl accepts vectors by rows.
        glUniformMatrix4fv(viewUID, 1, GL_FALSE, glm::value_ptr(viewM));
        glUniformMatrix4fv(projectionUID, 1, GL_FALSE, glm::value_ptr(projectionM));
        glUniformMatrix4fv(pvmUID, 1, GL_FALSE, glm::value_ptr(PVM));
    };
}