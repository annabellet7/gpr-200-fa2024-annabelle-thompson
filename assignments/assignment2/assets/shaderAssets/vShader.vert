#version 330 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec4 aColor;
layout (location = 2) in vec4 bColor;

uniform float uTime;

out vec4 primaryColor;
out vec4 complimentColor;


void main()
{
    vec4 pos = vec4(aPos, 1.0);
    pos.x = sin(uTime/2) * aPos.x;
    pos.y = sin(uTime) * aPos.y;
    gl_Position = pos;
    primaryColor = aColor;
    complimentColor = bColor;
}