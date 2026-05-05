#version 140
#define MAX_LIGHTS 64

in vec3 position;
in vec3 normal;
in vec2 textureCoord;

smooth out vec3 fragmentPosition;
smooth out vec3 fragmentNormal;
smooth out vec2 fragTexCoord;

uniform vec3 camPosition;
uniform mat4 normalMatrix;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
uniform mat4 PVM;

uniform float time;
uniform bool isVertexWave;

void main() {
    vec3 _position = position;

    if (isVertexWave) {
        float speed = 5.0;
        float frequency = 3.0;
        float amplitude = 0.04;

        _position.x += (sin(time * speed + (_position.x + _position.y + _position.z) * frequency) * amplitude) * _position.y;
    }

    fragmentPosition = vec3(model * vec4(_position, 1.0f));
    fragmentNormal = (normalMatrix * vec4(normal, 0.0f)).xyz;
    fragTexCoord = textureCoord;
    gl_Position = PVM * vec4(_position, 1.0f);
}