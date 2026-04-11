#ifndef PGR_SEM_COPAKOND_LIGHT_H
#define PGR_SEM_COPAKOND_LIGHT_H

#include "pgr.h"

namespace copakond {

class Light {

public:
    enum LightType {
        DIRECTIONAL,
        POINT,
        SPOTLIGHT
    };

private:
    LightType _type;

    glm::vec3 _position;
    glm::vec3 _direction;

    glm::vec3 _ambient;
    glm::vec3 _diffuse;
    glm::vec3 _specular;

    float _range;
    float _angle;
    bool _dim;

public:
    Light(LightType directionalLight, glm::vec3 direction, glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular);
    Light(LightType pointLight, glm::vec3 position, glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular, float range, bool dim);
    Light(LightType spotlightLight, glm::vec3 position, glm::vec3 direction, glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular,
        float range, float angle, bool dim);

    int type() { return _type; }
    glm::vec3 &position() { return _position; }
    glm::vec3 &direction() { return _direction; }

    glm::vec3 &ambient() { return _ambient; }
    glm::vec3 &diffuse() { return _diffuse; }
    glm::vec3 &specular() { return _specular; }

    float &range() { return _range; }
    float &angle() { return _angle; }
    bool &dimCoeff() { return _dim; }
};

}

#endif //PGR_SEM_COPAKOND_LIGHT_H
