#version 140
#define MAX_LIGHTS 64

smooth in vec3 fragmentPosition;
smooth in vec3 fragmentNormal;
out vec4 color;

uniform vec3 camPosition;

struct Material {
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    float shininess;
    float alpha;
};

struct Light {
    int type; // 0 = directional, 1 = point, 2 = spotlight

    vec3 position;
    vec3 direction;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;

    float range;
    float angle;
    float exponent;
    bool dim;
};

uniform Material material;
uniform Light lights[MAX_LIGHTS];
uniform int numLights;

vec3 calculateDirectionalL(Light light, vec3 fragmentPosition, vec3 fragmentNormal) {
    vec3 L = normalize(-light.direction);
    vec3 V = normalize(camPosition - fragmentPosition);
    vec3 R = reflect(-L, fragmentNormal);

    vec3 resColor = vec3(0.0f);
    resColor += material.ambient * light.ambient;
    resColor += material.diffuse * light.diffuse * max(dot(L, fragmentNormal), 0.0f);

    if (dot(L, fragmentNormal) > 0.0f) {
        resColor += material.specular * light.specular * pow(max(dot(R, V), 0.0f), material.shininess);
    }

    return resColor;
}

vec3 calculatePointL(Light light, vec3 fragmentPosition, vec3 fragmentNormal) {
    float dist = distance(fragmentPosition, light.position);

    if (dist > light.range) {
        return material.ambient;
    }

    vec3 L = normalize(light.position - fragmentPosition);
    vec3 R = reflect(-L, fragmentNormal);
    vec3 V = normalize(camPosition - fragmentPosition);

    vec3 resColor = vec3(0.0f);
    resColor += material.ambient * light.ambient;
    resColor += material.diffuse * light.diffuse * max(dot(L, fragmentNormal), 0.0f);

    if (dot(L, fragmentNormal) > 0.0f) {
        resColor += material.specular * light.specular * pow(max(dot(R, V), 0.0f), material.shininess);
    }

    if (light.dim) {
        float dimCoeff = 1.0f - (dist / light.range);
        resColor = mix(material.ambient, resColor, dimCoeff);
    }

    return resColor;
}

vec3 calculateSpotL(Light light, vec3 fragmentPosition, vec3 fragmentNormal) {
    float dist = distance(fragmentPosition, light.position);
    if (dist > light.range) {
        return material.ambient * light.ambient;
    }

    vec3 L = normalize(light.position - fragmentPosition);
    vec3 R = reflect(-L, fragmentNormal);
    vec3 V = normalize(camPosition - fragmentPosition);

    vec3 resColor = vec3(0.0f);
    float alpha_angle = dot(-L, normalize(light.direction));
    float spotlightEffect = pow(max(alpha_angle, 0.0), light.exponent);

    resColor += material.ambient * light.ambient;

    float cutoff = cos(radians(light.angle));
    if (alpha_angle >= cutoff) {
        resColor += material.diffuse * light.diffuse * max(dot(L, fragmentNormal), 0.0) * spotlightEffect;

        if (dot(L, fragmentNormal) > 0.0) {
            resColor += material.specular * light.specular * pow(max(dot(R, V), 0.0), material.shininess) * spotlightEffect;
        }

        // dim from the center lineary
        if (light.dim) {
            float distanceDimming = 1.0 - (dist / light.range);
            resColor = mix(material.ambient * light.ambient, resColor, distanceDimming);
        }

    } else {
        resColor = material.ambient * light.ambient;
    }

    return resColor;
}

vec3 calculateLight(Light light, vec3 fragmentPosition, vec3 fragmentNormal) {
    if (light.type == 0) {
        return calculateDirectionalL(light, fragmentPosition, fragmentNormal);
    } else if (light.type == 1) {
        return calculatePointL(light, fragmentPosition, fragmentNormal);
    } else if (light.type == 2) {
        return calculateSpotL(light, fragmentPosition, fragmentNormal);
    }

    return material.ambient;
}

void main() {
    vec3 normalizedNormal = normalize(fragmentNormal);

    vec3 resultColor = vec3(0.0f);
    for (int i = 0; i < numLights; ++i) {
        resultColor += calculateLight(lights[i], fragmentPosition, normalizedNormal);
    }

    color = vec4(resultColor, material.alpha);
}