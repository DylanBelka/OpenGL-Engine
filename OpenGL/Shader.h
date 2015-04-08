#ifndef SHADER_H
#define SHADER_H

#include <string>
#include <fstream>
#include <iostream>
#include <vector>
#include <sstream>

#include <glew.h>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/string_cast.hpp>

#include "camera.h"
#include "Transform.h"
#include "Texture.h"
#include "Light.h"

class Shader
{
public:
	Shader(const std::string& fileName);
	~Shader();

	void update(Camera& camera);
	void use();

	void pushLight(Light l);
	void pushLight(glm::vec3 pos, glm::vec3 color = glm::vec3(1.f, 1.f, 1.f));
	void popLight(Light light);
	void popLight();
	void drawLights();

	GLuint getProgram() { return program; }

private:
	GLuint createShader(const std::string& shaderSource, GLenum shaderType);
	BasicMesh createLightMesh();

private:

	enum shaders
	{
		VERTEX_SHADER,
		FRAGMENT_SHADER,

		NUM_SHADERS
	};

	GLuint program;
	GLuint shaders[NUM_SHADERS];

	enum uniforms
	{
		PROJECTION_UNIFORM,
		TEX_SAMPLER_UNIFORM,
		VIEW_POS_UNIFORM,

		NUM_UNIFORMS
	};

	enum lightsUniforms
	{
		NUM_LIGHTS_UNIFORM,

		NUM_LIGHT_UNIFORMS
	};

	GLuint newLightUniforms[NUM_LIGHT_UNIFORMS];

	std::vector<Light> lights;
	std::vector<GLuint> lightDirectionUniformLocations;
	std::vector<GLuint> lightColorUniformLocations;

	GLuint uniforms[uniforms::NUM_UNIFORMS];
	Texture white;
};

#endif // SHADER_H