#version 140

in vec3 textureCoord;
out vec4 color;

uniform float blendCoeff;
uniform samplerCube skyboxDay;
uniform samplerCube skyboxNight;

void main()
{
    vec3 flippedCoord = vec3(textureCoord.x, -textureCoord.y, textureCoord.z); // y flipped

    vec4 dayColor = texture(skyboxDay, flippedCoord);
    vec4 nightColor = texture(skyboxNight, flippedCoord);

    color = mix(dayColor, nightColor, blendCoeff);
}