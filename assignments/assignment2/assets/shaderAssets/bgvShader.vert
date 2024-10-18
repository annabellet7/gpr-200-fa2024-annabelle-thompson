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
    pos.y = abs(cos(uTime)) * aPos.y;
    vec2 texCoord = aTexCoord;
    texCoord.x *= 3;
    texCoord.y *= 3;
    gl_Position = pos;
    ourColor = aColor;
    TexCoord = texCoord;
}