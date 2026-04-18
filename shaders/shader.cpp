#include "shader.h"

namespace copakond {
    Shader::Shader() {
    }

    GLuint Shader::init(std::string vertShaderLocation, std::string fragShaderLocation) {
        while(glGetError() != GL_NO_ERROR); // for linux, flush all errors

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
        _shininess = glGetUniformLocation(_shaderProgram, "shininess");
        _alpha = glGetUniformLocation(_shaderProgram, "alpha");

        _numLights = glGetUniformLocation(_shaderProgram, "numLights");
        totalNumLights = 0;
        return _shaderProgram;
    }

    void Shader::setLight(Light* light, int index) {
        glUseProgram(_shaderProgram);

        std::string baseName = "lights[" + std::to_string(index) + "].";

        glUniform1i(glGetUniformLocation(_shaderProgram, (baseName + "type").c_str()), light->type());
        glUniform3fv(glGetUniformLocation(_shaderProgram, (baseName + "position").c_str()), 1, glm::value_ptr(light->position()));
        glUniform3fv(glGetUniformLocation(_shaderProgram, (baseName + "direction").c_str()), 1, glm::value_ptr(light->direction()));
        glUniform3fv(glGetUniformLocation(_shaderProgram, (baseName + "ambient").c_str()), 1, glm::value_ptr(light->ambient()));
        glUniform3fv(glGetUniformLocation(_shaderProgram, (baseName + "diffuse").c_str()), 1, glm::value_ptr(light->diffuse()));
        glUniform3fv(glGetUniformLocation(_shaderProgram, (baseName + "specular").c_str()), 1, glm::value_ptr(light->specular()));

        glUniform1f(glGetUniformLocation(_shaderProgram, (baseName + "range").c_str()), light->range());
        glUniform1f(glGetUniformLocation(_shaderProgram, (baseName + "angle").c_str()), light->angle());
        glUniform1f(glGetUniformLocation(_shaderProgram, (baseName + "exponent").c_str()), light->exponent());
        glUniform1i(glGetUniformLocation(_shaderProgram, (baseName + "dim").c_str()), light->dim());
        //glUniform1i(glGetUniformLocation(_shaderProgram, "numLights"), index+1);
    }

    void Shader::setNumLights(int count) {
        glUseProgram(_shaderProgram);
        glUniform1i(_numLights, count);
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
        glUniform1f(_shininess, mat->shininess());
        glUniform1f(_alpha, mat->alpha());
        mesh.draw();
    };
}
