#version 330 core
out vec4 FragColor;
out vec4 FragPos;

in vec4 primaryColor;
in vec4 complimentColor;
in vec4 pos;

uniform float uTime;

void main()
{
    vec4 newColor = primaryColor;
    vec4 newPos = pos;

    newPos.y = abs(sin(uTime) * pos.y);

    newColor.x = (abs(sin(uTime) * (primaryColor.x - complimentColor.x))) + primaryColor.x;
    newColor.y = (abs(sin(uTime) * (primaryColor.y - complimentColor.y))) + primaryColor.y;
    newColor.z = (abs(sin(uTime) * (primaryColor.z - complimentColor.z))) + primaryColor.z;

    FragColor = newColor;
    FragPos = newPos;
}