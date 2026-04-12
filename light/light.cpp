#include "light.h"

#include <iostream>

namespace copakond {
    Light::Light(LightType type, glm::vec3 position, glm::vec3 direction, glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular, float
        range, float angle, bool dim) :  _type(type), _position(position), _direction(direction), _ambient(ambient), _diffuse(diffuse),
        _specular(specular), _range (range), _angle(angle), _dim(dim) {}

    DirectionalLight::DirectionalLight(glm::vec3 direction, glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular)
        : Light(DIRECTIONAL, glm::vec3(0.0f), direction, ambient, diffuse, specular, 0.0f, 0.0f, false) {
    }

    PointLight::PointLight(glm::vec3 position, glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular, float range, bool dim)
        : Light(POINT, position, glm::vec3(0.0f), ambient, diffuse, specular, range, 360.0f, dim) {
    }

    SpotLight::SpotLight(glm::vec3 position, glm::vec3 direction, glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular, float range, float angle, bool dim)
        : Light(SPOTLIGHT, position, direction, ambient, diffuse, specular, range, angle, dim) {
    }
}
