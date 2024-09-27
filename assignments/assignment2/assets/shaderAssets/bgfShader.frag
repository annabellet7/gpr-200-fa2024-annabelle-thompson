#version 330 core
out vec4 FragColor;

in vec4 ourColor;
in vec2 TexCoord;

uniform sampler2D texture2;
uniform sampler2D texture3;
uniform float uTime;

void main()
{
   FragColor = mix(texture(texture2, TexCoord), texture(texture3, TexCoord), 0.4);
}