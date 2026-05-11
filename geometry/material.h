#ifndef PGR_SEM_COPAKOND_MATERIAL_H
#define PGR_SEM_COPAKOND_MATERIAL_H

#include "../pgr-portable.h"

#define DEFAULT_AMBIENT glm::vec3(1.0f, 1.0f, 1.0f)
#define DEFAULT_DIFFUSE glm::vec3(1.0f, 1.0f, 1.0f)
#define DEFAULT_SPECULAR glm::vec3(0.0f, 0.0f, 0.0f)
#define DEFAULT_ALPHA 1.0f
#define DEFAULT_SHININESS 32.0f

namespace copakond {
    /** @brief Defines surface properties and texture maps for rendering a mesh */
    class Material {
    protected:
        glm::vec3 _ambient;
        glm::vec3 _diffuse;
        glm::vec3 _specular;
        float _shininess;
        float _alpha;

        GLuint _diffuseTexture = 0;
        GLuint _specularTexture = 0;
        GLuint _shininessTexture = 0;
        GLuint _alphaTexture = 0;
        GLuint _normalTexture = 0;

        bool _hasDiffuseTexture;
        bool _hasSpecularTexture;
        bool _hasShininessTexture;
        bool _hasAlphaTexture;
        bool _hasNormalTexture;

        bool _isTextLabel = false; /**< Flag to indicate if material is for a text label (changes shader blend logic) */

        void constructor(const glm::vec3 &ambient, const glm::vec3 &diffuse, const glm::vec3 &specular, float shininess, float alpha);

    public:
        Material();
        Material(const glm::vec3 &ambient, const glm::vec3 &diffuse, const glm::vec3 &specular);
        Material(const glm::vec3 &ambient, const glm::vec3 &diffuse, const glm::vec3 &specular, float shininess);
        Material(const glm::vec3 &ambient, const glm::vec3 &diffuse, const glm::vec3 &specular, float shininess, float alpha);
        ~Material();

        // getters and setters
        glm::vec3 &ambient() { return _ambient; }
        glm::vec3 &diffuse() { return _diffuse; }
        glm::vec3 &specular() { return _specular; }
        float &shininess() { return _shininess; }
        float &alpha() { return _alpha; }

        // textures managers
        /**
         * @brief Loads and binds a diffuse texture map.
         * @param warpTexture If true, applies GL_REPEAT wrapping.
         * @param mipMap If true, generates mipmaps.
         */
        void setDiffuseTexture(const std::string &textureFile, bool warpTexture = false, bool mipMap = true);
        bool hasDiffuseTexture() const { return _hasDiffuseTexture; }
        void clearDiffuseTexture() { _hasDiffuseTexture = false; }

        void setSpecularTexture(const std::string &textureFile);
        bool hasSpecularTexture() const { return _hasSpecularTexture; }
        void clearSpecularTexture() { _hasSpecularTexture = false; }

        void setShininessTexture(const std::string &textureFile);
        bool hasShininessTexture() const { return _hasShininessTexture; }
        void clearShininessTexture() { _hasShininessTexture = false; }

        void setAlphaTexture(const std::string &textureFile);
        bool hasAlphaTexture() const { return _hasAlphaTexture; }
        void clearAlphaTexture() { _hasAlphaTexture = false; }

        void setNormalTexture(const std::string &textureFile);
        bool hasNormalTexture() const { return _hasNormalTexture; }
        void clearNormalTexture() { _hasNormalTexture = false; }

        GLuint diffuseTextureUniform() const { return _diffuseTexture; }
        GLuint specularTextureUniform() const { return _specularTexture; }
        GLuint shininessTextureUniform() const { return _shininessTexture; }
        GLuint alphaTextureUniform() const { return _alphaTexture; }
        GLuint normalTextureUniform() const { return _normalTexture; }

        void setAlpha(float alpha) { _alpha = alpha; }
        float getAlpha() const { return _alpha; }

        void setIsTextLabel(bool state) { _isTextLabel = state; }
        bool isTextLabel() const { return _isTextLabel; }

    };
}

#endif //PGR_SEM_COPAKOND_MATERIAL_H
