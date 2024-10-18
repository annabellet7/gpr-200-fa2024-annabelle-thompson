#version 330 core
out vec4 FragColor;

in vec4 ourColor;
in vec2 TexCoord;

uniform float uTime;
uniform sampler2D texture1;

void main()
{
   FragColor = texture(texture1, TexCoord);
}