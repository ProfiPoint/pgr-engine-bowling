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

        _worldAmbientUID = glGetUniformLocation(_shaderProgram, "worldAmbient");

        _ambient = glGetUniformLocation(_shaderProgram, "material.ambient");
        _diffuse = glGetUniformLocation(_shaderProgram, "material.diffuse");
        _specular = glGetUniformLocation(_shaderProgram, "material.specular");
        _shininess = glGetUniformLocation(_shaderProgram, "material.shininess");
        _alpha = glGetUniformLocation(_shaderProgram, "material.alpha");

        _diffuseMapUID = glGetUniformLocation(_shaderProgram, "textureData.diffuseMap");
        _specularMapUID = glGetUniformLocation(_shaderProgram, "textureData.specularMap");
        _shininessMapUID = glGetUniformLocation(_shaderProgram, "textureData.shininessMap");
        _alphaMapUID = glGetUniformLocation(_shaderProgram, "textureData.alphaMap");
        _normalMapUID = glGetUniformLocation(_shaderProgram, "textureData.normalMap");

        _useDiffuseMapUID = glGetUniformLocation(_shaderProgram, "textureData.useDiffuseMap");
        _useSpecularMapUID = glGetUniformLocation(_shaderProgram, "textureData.useSpecularMap");
        _useShininessMapUID = glGetUniformLocation(_shaderProgram, "textureData.useShininessMap");
        _useAlphaMapUID = glGetUniformLocation(_shaderProgram, "textureData.useAlphaMap");
        _useNormalMapUID = glGetUniformLocation(_shaderProgram, "textureData.useNormalMap");

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
        glUniform3fv(_worldAmbientUID, 1, glm::value_ptr(getWorldAmbient()));
    }

    void Shader::applyMaterialUniforms(std::shared_ptr<Material> mat) {
        if (!mat) return;

        glUniform3fv(_ambient, 1, glm::value_ptr(mat->ambient()));

        // SET DIFFUSE TEXTURE / DIFFUSE VECTOR
        if (mat->hasDiffuseTexture()) {
            glUniform1i(_useDiffuseMapUID, 1);
            glActiveTexture(GL_TEXTURE0);
            glBindTexture(GL_TEXTURE_2D, mat->diffuseTextureUniform());
            glUniform1i(_diffuseMapUID, 0);
        } else {
            glUniform3fv(_diffuse, 1, glm::value_ptr(mat->diffuse()));
            glUniform1i(_useDiffuseMapUID, 0);
        }

        // SET SPECULAR TEXTURE / SPECULAR VECTOR
        if (mat->hasSpecularTexture()) {
            glUniform1i(_useSpecularMapUID, 1);
            glActiveTexture(GL_TEXTURE1);
            glBindTexture(GL_TEXTURE_2D, mat->specularTextureUniform());
            glUniform1i(_specularMapUID, 1);
        } else {
            glUniform3fv(_specular, 1, glm::value_ptr(mat->specular()));
            glUniform1i(_useSpecularMapUID, 0);
        }

        // SET SHININESS TEXTURE / SHININESS FLOAT
        if (mat->hasShininessTexture()) {
            glUniform1i(_useShininessMapUID, 1);
            glActiveTexture(GL_TEXTURE2);
            glBindTexture(GL_TEXTURE_2D, mat->shininessTextureUniform());
            glUniform1i(_shininessMapUID, 2);
        } else {
            glUniform1f(_shininess, mat->shininess());
            glUniform1i(_useShininessMapUID, 0);
        }

        // SET ALPHA TEXTURE / ALPHA FLOAT
        if (mat->hasAlphaTexture()) {
            glUniform1i(_useAlphaMapUID, 1);
            glActiveTexture(GL_TEXTURE3);
            glBindTexture(GL_TEXTURE_2D, mat->alphaTextureUniform());
            glUniform1i(_alphaMapUID, 3);
        } else {
            glUniform1f(_alpha, mat->alpha());
            glUniform1i(_useAlphaMapUID, 0);
        }

        // SET NORMAL TEXTURE / NORMAL VECTOR
        if (mat->hasNormalTexture()) {
            glUniform1i(_useNormalMapUID, 1);
            glActiveTexture(GL_TEXTURE4);
            glBindTexture(GL_TEXTURE_2D, mat->normalTextureUniform());
        } else {
            glUniform1i(_useNormalMapUID, 4);
        }
    }

    void Shader::draw(Mesh &mesh, bool drawTransparent) {
        glm::mat4 modelM = mesh.getModelMatrix();
        glm::mat4 PVM = _projectionM * _viewM * modelM;
        glm::mat4 normalMatrix = glm::transpose(glm::inverse(modelM)); // correct matrix for non-rigid transform
        std::shared_ptr<Material> mat = mesh.getMaterial();

        if (!mat) {
            std::cerr << "ERROR: Mesh doesn't have any materials" << std::endl;
            exit(0);
        }

        // UNIFORM APPLY
        glUniformMatrix4fv(_modelUID, 1, GL_FALSE, glm::value_ptr(modelM)); // TRUE: M -> M^t, opengl accepts vectors by rows.
        glUniformMatrix4fv(_pvmUID, 1, GL_FALSE, glm::value_ptr(PVM));
        glUniformMatrix4fv(_normalMatrix, 1, GL_FALSE, glm::value_ptr(normalMatrix));

        glBindVertexArray(mesh.getVao());

        if (mesh.getSubMeshes().empty()) { // has only one material
            if ((mesh.getMaterial()->alpha() != 1.0f) == drawTransparent) { // draw if it should draw the correct mode non / transparent
                applyMaterialUniforms(mesh.getMaterial());
                mesh.draw();
            }
        } else {
            for (const auto& subMesh : mesh.getSubMeshes()) { // has multiple materials => iterating over subMeshes
                if ((subMesh.material->alpha() != 1.0f) == drawTransparent) { // draw if it should draw the correct mode non / transparent
                    applyMaterialUniforms(subMesh.material);

                    void* offset = (void*)(subMesh.indexOffset * sizeof(unsigned int));
                    glDrawElements(GL_TRIANGLES, subMesh.indexCount, GL_UNSIGNED_INT, offset);
                }
            }
        }
    };
}
