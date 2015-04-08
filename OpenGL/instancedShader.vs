#version 330 core

layout(location = 0) in vec3 position;

layout(location = 1) in vec2 uv;

layout(location = 2) in vec3 normal;

layout(location = 3) in mat4 model;

layout(location = 7) in mat4 view;

out vec2 UV;
out vec3 Normal;
out vec3 FragPos;

uniform mat4 projection;

void main()
{
	gl_Position = projection * view * model * vec4(position, 1.0);
	UV = uv;
	Normal = mat3(transpose(inverse(model))) * normal;
	FragPos = vec3(model * vec4(position, 1.0));
}