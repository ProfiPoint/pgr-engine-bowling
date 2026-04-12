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

vec4 calculatePointLight() {
    vec3 worldPos = vec3(model * vec4(position, 1.0));
    vec3 vertexNormal = normalize((normalMatrix * vec4(normal, 0.0)).xyz);

    float dist = distance(worldPos, light.position);

    if (dist > light.range) {
        return vec4(ambient, alpha);
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
        float attenuation = 1.0 - (dist / light.range);
        resColor = mix(ambient, resColor, attenuation);
    }

    return vec4(resColor, alpha);
}

void main() {
    vertexColor = calculatePointLight();
    gl_Position = PVM * vec4(position, 1.0f);
}