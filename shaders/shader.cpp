#include "shader.h"

#include <iostream>
#include <memory>

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

        _ambient = glGetUniformLocation(_shaderProgram, "material.ambient");
        _diffuse = glGetUniformLocation(_shaderProgram, "material.diffuse");
        _specular = glGetUniformLocation(_shaderProgram, "material.specular");
        _shininess = glGetUniformLocation(_shaderProgram, "material.shininess");
        _alpha = glGetUniformLocation(_shaderProgram, "material.alpha");

        _numLights = glGetUniformLocation(_shaderProgram, "numLights");
        totalNumLights = 0;
        return _shaderProgram;
    }

    void Shader::setLight(Light* light, int index) {
        light->id() = index;
        glUseProgram(_shaderProgram);

        std::string uniformLightId = "lights[" + std::to_string(index) + "].";

        LightUniforms &unifLocs = light->getUniformLocations();
        unifLocs.type = glGetUniformLocation(_shaderProgram, (uniformLightId + "type").c_str());
        unifLocs.position = glGetUniformLocation(_shaderProgram, (uniformLightId + "position").c_str());
        unifLocs.direction = glGetUniformLocation(_shaderProgram, (uniformLightId + "direction").c_str());
        unifLocs.ambient = glGetUniformLocation(_shaderProgram, (uniformLightId + "ambient").c_str());
        unifLocs.diffuse = glGetUniformLocation(_shaderProgram, (uniformLightId + "diffuse").c_str());
        unifLocs.specular = glGetUniformLocation(_shaderProgram, (uniformLightId + "specular").c_str());
        unifLocs.range = glGetUniformLocation(_shaderProgram, (uniformLightId + "range").c_str());
        unifLocs.angle = glGetUniformLocation(_shaderProgram, (uniformLightId + "angle").c_str());
        unifLocs.exponent = glGetUniformLocation(_shaderProgram, (uniformLightId + "exponent").c_str());
        unifLocs.dim = glGetUniformLocation(_shaderProgram, (uniformLightId + "dim").c_str());

        glUniform1i(glGetUniformLocation(_shaderProgram, "numLights"), index+1);
        updateLight(light);
    }

    void Shader::updateLight(Light* light) {
        glUseProgram(_shaderProgram);

        LightUniforms& unifLocs = light->getUniformLocations();

        glUniform1i(unifLocs.type, light->type());
        glUniform3fv(unifLocs.position, 1, glm::value_ptr(light->position()));
        glUniform3fv(unifLocs.direction, 1, glm::value_ptr(light->direction()));
        glUniform3fv(unifLocs.ambient, 1, glm::value_ptr(light->ambient()));
        glUniform3fv(unifLocs.diffuse, 1, glm::value_ptr(light->diffuse()));
        glUniform3fv(unifLocs.specular, 1, glm::value_ptr(light->specular()));
        glUniform1f(unifLocs.range, light->range());
        glUniform1f(unifLocs.angle, light->angle());
        glUniform1f(unifLocs.exponent, light->exponent());
        glUniform1i(unifLocs.dim, light->dim());

        std::cout << light->exponent() << std::endl;
        std::cout << light->range() << std::endl;
        std::cout << light->angle() << std::endl;
    }

    void Shader::update(Camera &camera, int winWidth, int winHeight) {
        glUseProgram(_shaderProgram);
        _viewM = camera.getViewMatrix();
        _projectionM = camera.getProjectionMatrix((float)winWidth, (float)winHeight);
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
