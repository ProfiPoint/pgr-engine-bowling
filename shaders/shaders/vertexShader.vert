#version 140

in vec3 position;
in vec3 normal;
smooth out vec4 vertexColor;

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

uniform vec3 camPosition;
uniform mat4 normalMatrix;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
uniform mat4 PVM;

uniform vec3 ambient;
uniform vec3 diffuse;
uniform vec3 specular;
uniform float shininess;
uniform float alpha;

uniform Light light;

vec3 calculateDirectionalL(Light light, vec3 worldPos, vec3 vertexNormal) {
    vec3 L = normalize(-light.direction);
    vec3 V = normalize(camPosition - worldPos);
    vec3 R = reflect(-L, vertexNormal);

    vec3 resColor = vec3(0.0f);
    resColor += ambient * light.ambient;
    resColor += diffuse * light.diffuse * max(dot(L, vertexNormal), 0.0f);

    if (dot(L, vertexNormal) > 0.0f) {
        resColor += specular * light.specular * pow(max(dot(R, V), 0.0f), shininess);
    }

    return resColor;
}

vec3 calculatePointL(Light light, vec3 worldPos, vec3 vertexNormal) {
    float dist = distance(worldPos, light.position);

    if (dist > light.range) {
        return ambient;
    }

    vec3 L = normalize(light.position - worldPos);
    vec3 R = reflect(-L, vertexNormal);
    vec3 V = normalize(camPosition - worldPos);

    vec3 resColor = vec3(0.0f);
    resColor += ambient * light.ambient;
    resColor += diffuse * light.diffuse * max(dot(L, vertexNormal), 0.0f);

    if (dot(L, vertexNormal) > 0.0f) {
        resColor += specular * light.specular * pow(max(dot(R, V), 0.0f), shininess);
    }

    if (light.dim) {
        float dimCoeff = 1.0f - (dist / light.range);
        resColor = mix(ambient, resColor, dimCoeff);
    }

    return resColor;
}

vec3 calculateSpotL(Light light, vec3 worldPos, vec3 vertexNormal) {
    float dist = distance(worldPos, light.position);
    if (dist > light.range) {
        return ambient * light.ambient;
    }

    vec3 L = normalize(light.position - worldPos);
    vec3 R = reflect(-L, vertexNormal);
    vec3 V = normalize(camPosition - worldPos);

    vec3 resColor = vec3(0.0f);
    float alpha_angle = dot(-L, normalize(light.direction));
    float spotlightEffect = pow(max(alpha_angle, 0.0), light.exponent);

    resColor += ambient * light.ambient;

    float cutoff = cos(radians(light.angle));
    if (alpha_angle >= cutoff) {
        resColor += diffuse * light.diffuse * max(dot(L, vertexNormal), 0.0) * spotlightEffect;

        if (dot(L, vertexNormal) > 0.0) {
            resColor += specular * light.specular * pow(max(dot(R, V), 0.0), shininess) * spotlightEffect;
        }

        // dim from the center lineary
        if (light.dim) {
            float distanceDimming = 1.0 - (dist / light.range);
            resColor = mix(ambient * light.ambient, resColor, distanceDimming);
        }

    } else {
        resColor = ambient * light.ambient;
    }

    return resColor;
}

vec3 calculateLight(Light light) {
    vec3 worldPos = vec3(model * vec4(position, 1.0));
    vec3 vertexNormal = normalize((normalMatrix * vec4(normal, 0.0)).xyz);

    if (light.type == 0) {
        return calculateDirectionalL(light, worldPos, vertexNormal);
    } else if (light.type == 1) {
        return calculatePointL(light, worldPos, vertexNormal);
    } else if (light.type == 2) {
        return calculateSpotL(light, worldPos, vertexNormal);
    }

    return ambient;
}

void main() {
    vertexColor = vec4(calculateLight(light), alpha);
    gl_Position = PVM * vec4(position, 1.0f);
}