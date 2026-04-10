#include "material.h"

namespace copakond {
    void Material::constructor(const glm::vec3 &ambient, const glm::vec3 &diffuse, const glm::vec3 &specular, float alpha, float shininess,
        const std::string &textureFile) {

        _ambient = ambient;
        _diffuse = diffuse;
        _specular = specular;
        _alpha = alpha;
        _shininess = shininess;

        // TODO: IMPLEMENT TEXTURE FILE PARSING
    }




    Material::Material() {
        constructor(DEFAULT_AMBIENT, DEFAULT_DIFFUSE, DEFAULT_SPECULAR, 1, 1, "");
    }
    Material::Material(const glm::vec3 &ambient, const glm::vec3 &diffuse, const glm::vec3 &specular) {
        constructor(ambient, diffuse, specular, 1, 1, "");
    }
    Material::Material(const glm::vec3 &ambient, const glm::vec3 &diffuse, const glm::vec3 &specular, float alpha) {
        constructor(ambient, diffuse, specular, alpha, 1, "");
    }
    Material::Material(const glm::vec3 &ambient, const glm::vec3 &diffuse, const glm::vec3 &specular, float alpha, float shininess) {
        constructor(ambient, diffuse, specular, alpha, shininess, "");
    }

    Material::Material(const std::string &textureFile) {
        constructor(DEFAULT_AMBIENT, DEFAULT_DIFFUSE, DEFAULT_SPECULAR, 1, 1, textureFile);
    }
    Material::Material(const std::string &textureFile, const glm::vec3 &specular) {
        constructor(DEFAULT_AMBIENT, DEFAULT_DIFFUSE, specular, 1, 1, textureFile);
    }
    Material::Material(const std::string &textureFile, const glm::vec3 &specular, float alpha) {
        constructor(DEFAULT_AMBIENT, DEFAULT_DIFFUSE, specular, alpha, 1, textureFile);
    }
    Material::Material(const std::string &textureFile, const glm::vec3 &specular, float alpha, float shininess) {
        constructor(DEFAULT_AMBIENT, DEFAULT_DIFFUSE, specular, alpha, shininess, textureFile);
    }
}