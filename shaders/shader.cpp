#include "shader.h"

namespace copakond {
    Shader::Shader() {
    }

    GLuint Shader::init(std::string vertShaderLocation, std::string fragShaderLocation) {
        GLuint shaders[] = {
            pgr::createShaderFromFile(GL_VERTEX_SHADER, vertShaderLocation),
            pgr::createShaderFromFile(GL_FRAGMENT_SHADER, fragShaderLocation),
            0
        };

        _shaderProgram = pgr::createProgram(shaders);

        // UNIFORM BINDING
        _modelUID = glGetUniformLocation(_shaderProgram, "model");
        _viewUID = glGetUniformLocation(_shaderProgram, "view");
        _projectionUID = glGetUniformLocation(_shaderProgram, "projection");
        _pvmUID = glGetUniformLocation(_shaderProgram, "PVM");
        _camPos = glGetUniformLocation(_shaderProgram, "camPosition");
        _normalMatrix = glGetUniformLocation(_shaderProgram, "normalMatrix");

        _ambient = glGetUniformLocation(_shaderProgram, "ambient");
        _diffuse = glGetUniformLocation(_shaderProgram, "diffuse");
        _specular = glGetUniformLocation(_shaderProgram, "specular");
        _alpha = glGetUniformLocation(_shaderProgram, "alpha");
        _shininess = glGetUniformLocation(_shaderProgram, "shininess");
        return _shaderProgram;
    }

    void Shader::update(Camera &camera, int winWidth, int winHeight) {
        glUseProgram(_shaderProgram);
        _viewM = camera.getViewMatrix();
        _projectionM = camera.getProjectionMatrix(winWidth, winHeight);
        _position = camera.getPosition();

        // UNIFORM APPLY
        glUniform3fv(_camPos, 1, glm::value_ptr(_position));
        glUniformMatrix4fv(_viewUID, 1, GL_FALSE, glm::value_ptr(_viewM));
        glUniformMatrix4fv(_projectionUID, 1, GL_FALSE, glm::value_ptr(_projectionM));
    }

    void Shader::draw(Mesh &mesh) {
        glm::mat4 modelM = mesh.getModelMatrix();
        glm::mat4 PVM = _projectionM * _viewM * modelM;
        glm::mat4 normalMatrix = glm::transpose(glm::inverse(modelM)); // correct matrix for non-rigid transform
        std::shared_ptr<Material> mat = mesh.getMaterial();

        // UNIFORM APPLY
        glUniformMatrix4fv(_modelUID, 1, GL_FALSE, glm::value_ptr(modelM)); // TRUE: M -> M^t, opengl accepts vectors by rows.
        glUniformMatrix4fv(_pvmUID, 1, GL_FALSE, glm::value_ptr(PVM));
        glUniformMatrix4fv(_normalMatrix, 1, GL_FALSE, glm::value_ptr(normalMatrix));

        glUniform3fv(_ambient, 1, glm::value_ptr(mat->ambient()));
        glUniform3fv(_diffuse, 1, glm::value_ptr(mat->diffuse()));
        glUniform3fv(_specular, 1, glm::value_ptr(mat->specular()));
        glUniform1f(_alpha, mat->alpha());
        glUniform1f(_shininess, mat->shininess());
        mesh.draw();
    };
}
