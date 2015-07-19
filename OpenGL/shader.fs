#version 330 core

in vec2 UV;
in vec3 Normal;
in vec3 FragPos;

out vec4 outputColor;

uniform sampler2D tex;
uniform vec3 lightDirection;
uniform vec3 viewPos;

#define MAX_LIGHTS 32 // array sizes must be compile time evaluated

uniform int numLights;
uniform vec3 lightPos[MAX_LIGHTS];
uniform vec3 lightColors[MAX_LIGHTS];

void main()
{
	const float specularStrength = 0.5f;
	const float ambientStrength = 0.1f;

	vec3 viewDir = normalize(viewPos - FragPos);
	vec3 norm = normalize(Normal);
	vec4 result;

	for (int i = 0; i < numLights; i++)
	{
		vec3 lightDir = normalize(lightPos[i] - FragPos);
		vec3 reflectDir = reflect(-lightDir, norm);

		vec3 ambient = ambientStrength * lightColors[i];

		float diff = max(dot(norm, lightDir), 0.0);
		vec3 diffuse = diff * lightColors[i];

		float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
		vec3 specular = specularStrength * spec * lightColors[i];

		result += vec4(ambient + diffuse + specular, 1.0);
	}

	outputColor = result * texture(tex, UV);
}
