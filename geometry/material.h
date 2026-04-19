#ifndef PGR_SEM_COPAKOND_MATERIAL_H
#define PGR_SEM_COPAKOND_MATERIAL_H

#include "../pgr-portable.h"

#define DEFAULT_AMBIENT glm::vec3(0.25f, 0.25f, 0.25f)
#define DEFAULT_DIFFUSE glm::vec3(1.0f, 1.0f, 1.0f)
#define DEFAULT_SPECULAR glm::vec3(1.0f, 1.0f, 1.0f)
#define DEFAULT_ALPHA 1.0f
#define DEFAULT_SHININESS 64.0f

namespace copakond {
    class Material {
    protected:
        glm::vec3 _ambient;
        glm::vec3 _diffuse;
        glm::vec3 _specular;
        float _shininess;
        float _alpha;

        GLuint _texture;
        bool _hasTexture;

        void constructor(const glm::vec3 &ambient, const glm::vec3 &diffuse, const glm::vec3 &specular, float shininess, float alpha,
                         const std::string &textureFile);

        void _setMaterial(const Material &material);

    public:
        // color
        Material();
        Material(const glm::vec3 &ambient, const glm::vec3 &diffuse, const glm::vec3 &specular);
        Material(const glm::vec3 &ambient, const glm::vec3 &diffuse, const glm::vec3 &specular, float shininess);
        Material(const glm::vec3 &ambient, const glm::vec3 &diffuse, const glm::vec3 &specular, float shininess, float alpha);

        // texture
        Material(const std::string &textureFile);
        Material(const std::string &textureFile, const glm::vec3 &specular);
        Material(const std::string &textureFile, const glm::vec3 &specular, float shininess);
        Material(const std::string &textureFile, const glm::vec3 &specular, float shininess, float alpha);

        // getters and setters
        glm::vec3 &ambient() { return _ambient; }
        glm::vec3 &diffuse() { return _diffuse; }
        glm::vec3 &specular() { return _specular; }
        float &shininess() { return _shininess; }
        float &alpha() { return _alpha; }

        // texture managers
        void setTexture(const std::string &textureFile);
        bool hasTexture() { return _hasTexture; }
        void clearTexture() { _hasTexture = false; }
    };
}

#endif //PGR_SEM_COPAKOND_MATERIAL_H
