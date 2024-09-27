#version 330 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec4 aColor;
layout (location = 2) in vec2 aTexCoord;

uniform float uTime;

out vec4 ourColor;
out vec2 TexCoord;

void main()
{
    vec4 pos = vec4(aPos, 1.0);
    pos.y = abs(sin(uTime/2.5)) + aPos.y;
    gl_Position = pos;
    ourColor = aColor;
    TexCoord = aTexCoord;
}