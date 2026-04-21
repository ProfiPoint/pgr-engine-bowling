#version 140

in vec3 textureCoord;
out vec4 color;

uniform samplerCube skybox;

void main()
{
    color = texture(skybox, textureCoord);
}