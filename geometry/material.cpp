#include "material.h"

namespace copakond {
    void Material::constructor(const glm::vec3 &ambient, const glm::vec3 &diffuse, const glm::vec3 &specular, float shininess, float alpha,
        const std::string &textureFile) {

        _ambient = ambient;
        _diffuse = diffuse;
        _specular = specular;
        _alpha = alpha;
        _shininess = shininess;

        setTexture(textureFile);
    }

    void Material::setTexture(const std::string &textureFile) {
        if (textureFile == "") { return; }

        // TODO: IMPLEMENT TEXTURE FILE PARSING
    }

    Material::Material() {
        constructor(DEFAULT_AMBIENT, DEFAULT_DIFFUSE, DEFAULT_SPECULAR, DEFAULT_SHININESS, DEFAULT_ALPHA, "");
    }
    Material::Material(const glm::vec3 &ambient, const glm::vec3 &diffuse, const glm::vec3 &specular) {
        constructor(ambient, diffuse, specular, DEFAULT_SHININESS, DEFAULT_ALPHA, "");
    }
    Material::Material(const glm::vec3 &ambient, const glm::vec3 &diffuse, const glm::vec3 &specular, float shininess) {
        constructor(ambient, diffuse, specular, shininess, DEFAULT_ALPHA, "");
    }
    Material::Material(const glm::vec3 &ambient, const glm::vec3 &diffuse, const glm::vec3 &specular, float shininess, float alpha) {
        constructor(ambient, diffuse, specular, shininess, alpha, "");
    }

    Material::Material(const std::string &textureFile) {
        constructor(DEFAULT_AMBIENT, DEFAULT_DIFFUSE, DEFAULT_SPECULAR, DEFAULT_SHININESS, DEFAULT_ALPHA, textureFile);
    }
    Material::Material(const std::string &textureFile, const glm::vec3 &specular) {
        constructor(DEFAULT_AMBIENT, DEFAULT_DIFFUSE, specular, DEFAULT_SHININESS, DEFAULT_ALPHA, textureFile);
    }
    Material::Material(const std::string &textureFile, const glm::vec3 &specular, float shininess) {
        constructor(DEFAULT_AMBIENT, DEFAULT_DIFFUSE, specular, shininess, DEFAULT_ALPHA, textureFile);
    }
    Material::Material(const std::string &textureFile, const glm::vec3 &specular, float shininess, float alpha) {
        constructor(DEFAULT_AMBIENT, DEFAULT_DIFFUSE, specular, shininess, alpha, textureFile);
    }


}