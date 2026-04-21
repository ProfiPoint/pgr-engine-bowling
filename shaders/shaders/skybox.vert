#version 140

in vec3 position;
out vec3 textureCoord;

uniform mat4 view;
uniform mat4 projection;

void main()
{
    textureCoord = position;
    vec4 pos = projection * view * vec4(position, 1.0); // clipping space
    gl_Position = vec4(pos.x, pos.y, pos.w * 0.999, pos.w); // perspective division w/w = depth = 1
}