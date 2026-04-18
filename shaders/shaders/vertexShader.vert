#version 140
#define MAX_LIGHTS 64

in vec3 position;
in vec3 normal;
smooth out vec3 fragmentPosition;
smooth out vec3 fragmentNormal;

uniform vec3 camPosition;
uniform mat4 normalMatrix;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
uniform mat4 PVM;

void main() {
    fragmentPosition = vec3(model * vec4(position, 1.0));
    fragmentNormal = (normalMatrix * vec4(normal, 0.0)).xyz;
    gl_Position = PVM * vec4(position, 1.0);
}