#version 140

in vec3 position;
in vec3 normal;
smooth out vec4 vertexColor;

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

vec4 calculateLight() {
    vec3 worldPos = vec3(model * vec4(position, 1.0));
    vec3 vertexNormal = normalize((normalMatrix * vec4(normal, 0.0)).xyz);

    vec3 lightPosition = vec3(10.0f, 10.0f, 10.0f);
    vec3 lightAmbient = vec3(1.0f, 1.0f, 1.0f);
    vec3 lightDiffuse = vec3(1.0f, 1.0f, 1.0f);
    vec3 lightSpecular = vec3(1.0f, 1.0f, 1.0f);

    vec3 resColor = vec3(0.0f);
    vec3 L = normalize(lightPosition - worldPos);
    vec3 R = reflect(-L, vertexNormal);
    vec3 V = normalize(camPosition - worldPos);

    resColor += ambient * lightAmbient;
    resColor += diffuse * lightDiffuse * max(dot(L, vertexNormal), 0.0f);

    if (dot(L, vertexNormal) > 0.0f) {
        resColor += specular * lightSpecular * pow(max(dot(R, V), 0.0f), shininess);
    }

    return vec4(resColor,alpha);
}

void main() {
    vertexColor = calculateLight();
    gl_Position = PVM * vec4(position, 1.0f);
}