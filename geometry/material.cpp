#include "material.h"

namespace copakond {
    void Material::constructor(const glm::vec3 &ambient, const glm::vec3 &diffuse, const glm::vec3 &specular, float shininess, float alpha) {

        _ambient = ambient;
        _diffuse = diffuse;
        _specular = specular;
        _alpha = alpha;
        _shininess = shininess;

    }

    void Material::setAmbientTexture(const std::string &textureFile) {
        if (textureFile == "") { return; }

        // TODO: IMPLEMENT TEXTURE FILE PARSING
    }

    void Material::setDiffuseTexture(const std::string &textureFile) {
        if (textureFile == "") { return; }

        // TODO: IMPLEMENT TEXTURE FILE PARSING
    }

    void Material::setSpecularTexture(const std::string &textureFile) {
        if (textureFile == "") { return; }

        // TODO: IMPLEMENT TEXTURE FILE PARSING
    }

    void Material::setAlphaTexture(const std::string &textureFile) {
        if (textureFile == "") { return; }

        // TODO: IMPLEMENT TEXTURE FILE PARSING
    }

    void Material::setNormalTexture(const std::string &textureFile) {
        if (textureFile == "") { return; }

        // TODO: IMPLEMENT TEXTURE FILE PARSING
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