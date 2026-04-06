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
        M_unfId = glGetUniformLocation(shaderProgram, "model");
        V_unfId = glGetUniformLocation(shaderProgram, "view");
        P_unfId = glGetUniformLocation(shaderProgram, "projection");
        PVM_unfId = glGetUniformLocation(shaderProgram, "PVM");
        return shaderProgram;
    }

    void Shader::draw(Camera camera, int WIN_WIDTH, int WIN_HEIGHT) {
        glUseProgram(shaderProgram);

        // TODO: CHANGE THIS: USING DEFAILT MODEL MATRIX
        glm::mat4 modelM = glm::mat4(1.0f);
        glm::mat4 viewM = camera.getViewMatrix();
        glm::mat4 projectionM = camera.getProjectionMatrix(WIN_WIDTH, WIN_HEIGHT);
        glm::mat4 PVM = projectionM * viewM * modelM;

        // UNIFORM APPLY
        glUniformMatrix4fv(M_unfId, 1, GL_FALSE, glm::value_ptr(modelM)); // TRUE: M -> M^t, opengl accepts vectors by rows.
        glUniformMatrix4fv(V_unfId, 1, GL_FALSE, glm::value_ptr(viewM));
        glUniformMatrix4fv(P_unfId, 1, GL_FALSE, glm::value_ptr(projectionM));
        glUniformMatrix4fv(PVM_unfId, 1, GL_FALSE, glm::value_ptr(PVM));
    };
}