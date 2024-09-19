#version 330 core
out vec4 FragColor;

in vec4 primaryColor;
in vec4 complimentColor;

uniform float uTime;

void main()
{
    vec4 newColor = primaryColor;

    newColor.x = (abs(sin(uTime) * (primaryColor.x - complimentColor.x))) + primaryColor.x;
    newColor.y = (abs(sin(uTime) * (primaryColor.y - complimentColor.y))) + primaryColor.y;
    newColor.z = (abs(sin(uTime) * (primaryColor.z - complimentColor.z))) + primaryColor.z;

    FragColor = newColor;
}