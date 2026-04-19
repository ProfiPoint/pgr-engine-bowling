#ifndef PGR_SEM_COPAKOND_MATERIAL_H
#define PGR_SEM_COPAKOND_MATERIAL_H

#include "../pgr-portable.h"

#define DEFAULT_AMBIENT glm::vec3(1.0f, 1.0f, 1.0f)
#define DEFAULT_DIFFUSE glm::vec3(1.0f, 1.0f, 1.0f)
#define DEFAULT_SPECULAR glm::vec3(0.0f, 0.0f, 0.0f)
#define DEFAULT_ALPHA 1.0f
#define DEFAULT_SHININESS 32.0f

namespace copakond {
    class Material {
    protected:
        glm::vec3 _ambient;
        glm::vec3 _diffuse;
        glm::vec3 _specular;
        float _shininess;
        float _alpha;

        GLuint _diffuseTexture;
        GLuint _specularTexture;
        GLuint _shininessTexture;
        GLuint _alphaTexture;
        GLuint _normalTexture;

        bool _hasDiffuseTexture;
        bool _hasSpecularTexture;
        bool _hasShininessTexture;
        bool _hasAlphaTexture;
        bool _hasNormalTexture;

        void constructor(const glm::vec3 &ambient, const glm::vec3 &diffuse, const glm::vec3 &specular, float shininess, float alpha);

        void _setMaterial(const Material &material);

    public:
        Material();
        Material(const glm::vec3 &ambient, const glm::vec3 &diffuse, const glm::vec3 &specular);
        Material(const glm::vec3 &ambient, const glm::vec3 &diffuse, const glm::vec3 &specular, float shininess);
        Material(const glm::vec3 &ambient, const glm::vec3 &diffuse, const glm::vec3 &specular, float shininess, float alpha);

        // getters and setters
        glm::vec3 &ambient() { return _ambient; }
        glm::vec3 &diffuse() { return _diffuse; }
        glm::vec3 &specular() { return _specular; }
        float &shininess() { return _shininess; }
        float &alpha() { return _alpha; }

        // texture managers
        void setDiffuseTexture(const std::string &textureFile);
        bool hasDiffuseTexture() { return _hasDiffuseTexture; }
        void clearDiffuseTexture() { _hasDiffuseTexture = false; }

        void setSpecularTexture(const std::string &textureFile);
        bool hasSpecularTexture() { return _hasSpecularTexture; }
        void clearSpecularTexture() { _hasSpecularTexture = false; }

        void setShininessTexture(const std::string &textureFile);
        bool hasShininessTexture() { return _hasShininessTexture; }
        void clearShininessTexture() { _hasShininessTexture = false; }

        void setAlphaTexture(const std::string &textureFile);
        bool hasAlphaTexture() { return _hasAlphaTexture; }
        void clearAlphaTexture() { _hasAlphaTexture = false; }

        void setNormalTexture(const std::string &textureFile);
        bool hasNormalTexture() { return _hasNormalTexture; }
        void clearNormalTexture() { _hasNormalTexture = false; }

        GLuint diffuseTextureUniform() const { return _diffuseTexture; }
        GLuint specularTextureUniform() const { return _specularTexture; }
        GLuint shininessTextureUniform() const { return _shininessTexture; }
        GLuint alphaTextureUniform() const { return _alphaTexture; }
        GLuint normalTextureUniform() const { return _normalTexture; }

    };
}

#endif //PGR_SEM_COPAKOND_MATERIAL_H
