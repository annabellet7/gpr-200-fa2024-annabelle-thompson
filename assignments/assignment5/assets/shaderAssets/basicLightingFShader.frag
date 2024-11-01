#version 330 core
out vec4 FragColor;

in vec2 TexCoord;
in vec3 FragPos;
in vec3 Normal;

uniform sampler2D texture2;
uniform sampler2D texture3;

uniform float uTime;

uniform vec3 uLightColor;
uniform vec3 uLightPos;
uniform vec3 uViewPos;

void main()
{
	float ambientStrength = 0.15;
	vec3 ambient = ambientStrength * uLightColor;

	vec4 cubeTexture = mix(texture(texture2, TexCoord), texture(texture3, TexCoord), 0.4);
	vec3 norm = normalize(Normal);

	vec3 lightDir = normalize(uLightPos - FragPos);
	float diff = max(dot(norm, lightDir), 0.0);
	vec3 diffuse = diff * uLightColor;

	vec3 viewDir = normalize(uViewPos - FragPos);
	vec3 halfwayDir = normalize(lightDir + viewDir);
	float spec = pow(max(dot(norm, halfwayDir), 0.0), 32.0);
	vec3  specular = uLightColor * spec;

	vec3 result = (ambient + diffuse + specular) * vec3(cubeTexture.x, cubeTexture.y, cubeTexture.z);
	FragColor = vec4(result, 1.0);
}