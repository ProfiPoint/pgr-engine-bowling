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
        _shininess = glGetUniformLocation(_shaderProgram, "shininess");
        _alpha = glGetUniformLocation(_shaderProgram, "alpha");

        _lightType = glGetUniformLocation(_shaderProgram, "light.type");
        _lightPos  = glGetUniformLocation(_shaderProgram, "light.position");
        _lightDir  = glGetUniformLocation(_shaderProgram, "light.direction");
        _lightAmb  = glGetUniformLocation(_shaderProgram, "light.ambient");
        _lightDiff = glGetUniformLocation(_shaderProgram, "light.diffuse");
        _lightSpec = glGetUniformLocation(_shaderProgram, "light.specular");
        _lightRange = glGetUniformLocation(_shaderProgram, "light.range");
        _lightAngle = glGetUniformLocation(_shaderProgram, "light.angle");
        _lightDim = glGetUniformLocation(_shaderProgram, "light.dim");
        return _shaderProgram;
    }

    void Shader::setLight(Light* light) {
        glUseProgram(_shaderProgram);

        glUniform1i(_lightType, light->type());

        glUniform3fv(_lightPos, 1, glm::value_ptr(light->position()));
        glUniform3fv(_lightDir, 1, glm::value_ptr(light->direction()));
        glUniform3fv(_lightAmb, 1, glm::value_ptr(light->ambient()));
        glUniform3fv(_lightDiff, 1, glm::value_ptr(light->diffuse()));
        glUniform3fv(_lightSpec, 1, glm::value_ptr(light->specular()));
        glUniform1f(_lightRange, light->range());
        glUniform1f(_lightAngle, light->angle());
        glUniform1i(_lightDim, light->dim());
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
