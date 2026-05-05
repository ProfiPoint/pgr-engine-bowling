#version 140
#define FLAG_SPEED 5.0
#define FLAG_FREQUENCY 3.0
#define FLAG_AMPLITUDE 0.04

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
        float waveX = sin(time * FLAG_SPEED * 1.1 + _position.y * FLAG_FREQUENCY);
        float waveY = cos(time * FLAG_SPEED * 1.3 + (_position.x + _position.z) * FLAG_FREQUENCY * 0.5);
        float waveZ = sin(time * FLAG_SPEED * 0.9 + _position.y * FLAG_FREQUENCY * 1.2);

        _position.x += waveX * FLAG_AMPLITUDE * _position.z;
        _position.y += waveY * FLAG_AMPLITUDE * _position.x;
        _position.z += waveZ * FLAG_AMPLITUDE * _position.y;
    }

    fragmentPosition = vec3(model * vec4(_position, 1.0f));
    fragmentNormal = (normalMatrix * vec4(normal, 0.0f)).xyz;
    fragTexCoord = textureCoord;
    gl_Position = PVM * vec4(_position, 1.0f);
}