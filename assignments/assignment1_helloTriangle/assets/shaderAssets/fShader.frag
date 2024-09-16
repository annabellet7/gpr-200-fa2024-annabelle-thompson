#version 330 core
out vec4 FragColor;

in vec3 ourColor;
uniform float uTime;

void main()
{
    vec3 newColor = ourColor;
    //newColor.x = (abs(sin(uTime) * .047f)) + ourColor.x;
    //newColor.y = abs(sin(uTime))/2;
    newColor.z = (abs(sin(uTime) * .047)) + ourColor.z;
    FragColor = vec4(newColor, 1.0f);
}