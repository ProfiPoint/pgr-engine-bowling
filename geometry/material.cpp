#include "material.h"

namespace copakond {
    void Material::constructor(const glm::vec3 &ambient, const glm::vec3 &diffuse, const glm::vec3 &specular, float shininess, float alpha) {

        _ambient = ambient;
        _diffuse = diffuse;
        _specular = specular;
        _alpha = alpha;
        _shininess = shininess;

        _hasDiffuseTexture = false;
        _hasSpecularTexture = false;
        _hasShininessTexture = false;
        _hasAlphaTexture = false;
        _hasNormalTexture = false;

        _isTextLabel = false;
    }

    Material::~Material() {
        if (_hasDiffuseTexture) glDeleteTextures(1, &_diffuseTexture);
        if (_hasSpecularTexture) glDeleteTextures(1, &_specularTexture);
        if (_hasShininessTexture) glDeleteTextures(1, &_shininessTexture);
        if (_hasAlphaTexture) glDeleteTextures(1, &_alphaTexture);
        if (_hasNormalTexture) glDeleteTextures(1, &_normalTexture);
    }

    void Material::setDiffuseTexture(const std::string &textureFile, bool mipmap) {
        if (textureFile == "") { return; }
        _diffuseTexture = pgr::createTexture(textureFile, mipmap);
        _hasDiffuseTexture = true;
    }

    void Material::setSpecularTexture(const std::string &textureFile) {
        if (textureFile == "") { return; }
        _specularTexture = pgr::createTexture(textureFile);
        _hasSpecularTexture = true;
    }

    void Material::setShininessTexture(const std::string &textureFile) {
        if (textureFile == "") { return; }
        _shininessTexture = pgr::createTexture(textureFile);
        _hasShininessTexture = true;
    }

    void Material::setAlphaTexture(const std::string &textureFile) {
        if (textureFile == "") { return; }
        _alphaTexture = pgr::createTexture(textureFile);
        _hasAlphaTexture = true;
    }

    void Material::setNormalTexture(const std::string &textureFile) {
        if (textureFile == "") { return; }
        _normalTexture = pgr::createTexture(textureFile);
        _hasNormalTexture = true;
    }

    Material::Material() {
        constructor(DEFAULT_AMBIENT, DEFAULT_DIFFUSE, DEFAULT_SPECULAR, DEFAULT_SHININESS, DEFAULT_ALPHA);
    }
    Material::Material(const glm::vec3 &ambient, const glm::vec3 &diffuse, const glm::vec3 &specular) {
        constructor(ambient, diffuse, specular, DEFAULT_SHININESS, DEFAULT_ALPHA);
    }
    Material::Material(const glm::vec3 &ambient, const glm::vec3 &diffuse, const glm::vec3 &specular, float shininess) {
        constructor(ambient, diffuse, specular, shininess, DEFAULT_ALPHA);
    }
    Material::Material(const glm::vec3 &ambient, const glm::vec3 &diffuse, const glm::vec3 &specular, float shininess, float alpha) {
        constructor(ambient, diffuse, specular, shininess, alpha);
    }


}