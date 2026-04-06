#version 140

in vec3 position;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
uniform mat4 PVM;

void main() {
    gl_Position = PVM * vec4(position, 1.0f);
}