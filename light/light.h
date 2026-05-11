#ifndef PGR_SEM_COPAKOND_LIGHT_H
#define PGR_SEM_COPAKOND_LIGHT_H

#include "../pgr-portable.h"

namespace copakond {

/** @brief Caches shader uniform locations for a specific light instance to avoid repeated lookups */
struct LightUniforms {
    GLint type;
    GLint position;
    GLint direction;
    GLint ambient;
    GLint diffuse;
    GLint specular;
    GLint range;
    GLint angle;
    GLint exponent;
    GLint dim;
};

/** @brief Base class for scene lighting calculations */
class Light {
public:
    enum LightType {
        DIRECTIONAL,
        POINT,
        SPOTLIGHT
    };

protected:
    LightType _type;

    glm::vec3 _position;
    glm::vec3 _direction;

    glm::vec3 _ambient;
    glm::vec3 _diffuse;
    glm::vec3 _specular;

    int _id;
    float _range; /**< Maximum distance the light reaches */
    float _angle; /**< Cutoff angle for spotlights */
    float _exponent; /**< Falloff exponent for spotlights */
    bool _dim; /**< If true, light intensity attenuates based on distance */
    LightUniforms _uniformLocations;

public:
    /**
     * @brief Initializes base light properties.
     * @param dim If true, applies distance-based attenuation (dimming).
     */
    Light(LightType type, glm::vec3 position, glm::vec3 direction, glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular, float range,
        float angle, float exponent, bool dim);

    int type() { return _type; }
    glm::vec3 &position() { return _position; }
    glm::vec3 &direction() { return _direction; }

    glm::vec3 &ambient() { return _ambient; }
    glm::vec3 &diffuse() { return _diffuse; }
    glm::vec3 &specular() { return _specular; }

    int &id() { return _id; }
    float &range() { return _range; }
    float &angle() { return _angle; }
    float &exponent() { return _exponent; }
    bool &dim() { return _dim; }

    LightUniforms& getUniformLocations() { return _uniformLocations; }
};

class DirectionalLight : public Light {
public:
    DirectionalLight(glm::vec3 direction, glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular);
};

class PointLight : public Light {
public:
    PointLight(glm::vec3 position, glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular, float range, bool dim);
};

class SpotLight : public Light {
public:
    SpotLight(glm::vec3 position, glm::vec3 direction, glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular, float range, float
        angle, float exponent, bool dim);
};

}

#endif //PGR_SEM_COPAKOND_LIGHT_H
