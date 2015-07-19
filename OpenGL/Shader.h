#ifndef SHADER_H
#define SHADER_H

#include <string>
#include <fstream>
#include <iostream>
#include <vector>
#include <sstream>

#include <glew.h>

#include "camera.h"
#include "Light.h"

class Shader
{
public:
	Shader(const std::string& fileName);
	~Shader();

	void update(Camera& camera);
	void use();

	void pushLight(Light l);
	void popLight(Light light);
	void popLight();
	void drawLights();

	GLuint getProgram() { return program; }

	std::vector<Light> getLights() { return lights; }

private:
	GLuint createShader(const std::string& shaderSource, GLenum shaderType);

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

	GLuint numLightsUniform;

	std::vector<Light> lights;
#define MAX_LIGHTS	32
	std::vector<GLuint> lightPosUniformLocations;	// memory locations of the positions of the lights
	std::vector<GLuint> lightColorUniformLocations;		// memory locations of the colors of the lights

	GLuint uniforms[NUM_UNIFORMS];
};

#endif // SHADER_H