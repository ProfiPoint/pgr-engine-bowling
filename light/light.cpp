#include "light.h"

#include <iostream>

namespace copakond {
    Light::Light(LightType directionalLight, glm::vec3 direction, glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular) {
        if (directionalLight != DIRECTIONAL) {
            std::cout << "ERROR: This template is for DIRECTIONAL light" << std::endl;
            return;
        }

        _type = directionalLight;
        _position = direction;
        _direction = direction;
        _ambient = ambient;
        _diffuse = diffuse;
        _specular = specular;
        _range = 0;
        _angle = 0;
        _dim = false;

    }
    Light::Light(LightType pointLight, glm::vec3 position, glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular, float range, bool
        dim) {
        if (pointLight != POINT) {
            std::cout << "ERROR: This template is for POINT light" << std::endl;
            return;
        }

        _type = pointLight;
        _position = position;
        _direction = position;
        _ambient = ambient;
        _diffuse = diffuse;
        _specular = specular;
        _range = range;
        _angle = 0;
        _dim = dim;

    }
    Light::Light(LightType spotlightLight, glm::vec3 position, glm::vec3 direction, glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular,
        float range, float angle, bool dim) {
        if (spotlightLight != SPOTLIGHT) {
            std::cout << "ERROR: This template is for SPOTLIGHT light" << std::endl;
            return;
        }

        _type = spotlightLight;
        _position = position;
        _direction = direction;
        _ambient = ambient;
        _diffuse = diffuse;
        _specular = specular;
        _range = range;
        _angle = angle;
        _dim = dim;
    }
}
