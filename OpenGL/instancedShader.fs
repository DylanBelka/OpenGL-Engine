#version 330 core

in vec2 UV;
in vec3 Normal;
in vec3 FragPos;

out vec4 outputColor;

uniform sampler2D tex;
uniform vec3 lightDirection;
uniform vec3 viewPos;

#define MAX_LIGHTS 32 // array sizes must be compile time evaluated
const float ambientStrength = .1;

uniform int numLights;

uniform vec3 lightDirs[MAX_LIGHTS];
uniform vec3 lightColors[MAX_LIGHTS];

const float specularStrength = .5f;

void main()
{
	vec4 lightFinal = vec4(0.0, 0.0, 0.0, 1.0);
	for (int i = 0; i < numLights; i++)
	{
		vec3 norm = normalize(Normal);
		//vec3 lightDir = normalize(-lightDirs[i]);
		vec3 lightDir = normalize(lightDirs[i] - FragPos);
		float diff = max(dot(norm, lightDir), 0.0);
		vec3 diffuse = diff * lightColors[i];

		vec3 ambient = ambientStrength * lightColors[i];

		vec3 viewDir = normalize(viewPos - FragPos);
		vec3 reflectDir = reflect(-lightDir, norm);
		float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
		vec3 specular = specularStrength * spec * lightColors[i];

		lightFinal += (vec4(ambient, 1.0) + vec4(diffuse, 1.0) + vec4(specular, 1.0)); 
	}
	
	vec4 result = lightFinal * texture(tex, UV);

	if (result.a < .5)
		discard;

    outputColor = result;
}
