#include "Shader.h"

std::string fileLoader(const std::string& fileName);
GLuint createShader(const std::string& shaderSource, GLenum shaderType);

Shader::Shader(const std::string& fileName)
{
	program = glCreateProgram();

	std::string vertexShaderSource = fileLoader(fileName + ".vs");
	std::string fragmentShaderSource = fileLoader(fileName + ".fs");

	shaders[VERTEX_SHADER] = createShader(vertexShaderSource, GL_VERTEX_SHADER);
	shaders[FRAGMENT_SHADER] = createShader(fragmentShaderSource, GL_FRAGMENT_SHADER);

	for (unsigned i = 0; i < NUM_SHADERS; i++)
	{
		glAttachShader(program, shaders[i]);
	}
	 
	glLinkProgram(program);
	GLint linked;
	glGetProgramiv(program, GL_LINK_STATUS, &linked);
	if (!linked)
	{
		std::cerr << "Shader program linking failed" << std::endl;
	}
	
	uniforms[PROJECTION_UNIFORM] = glGetUniformLocation(program, "projection");
	uniforms[TEX_SAMPLER_UNIFORM] = glGetUniformLocation(program, "tex");
	newLightUniforms[NUM_LIGHTS_UNIFORM] = glGetUniformLocation(program, "numLights");
	uniforms[VIEW_POS_UNIFORM] = glGetUniformLocation(program, "viewPos");

	//lights.push_back(Light(glm::vec3(1.2f, 1.0f, 2.0f), glm::vec3(1.0, 1.0, 1.0)));	// world light
	/*
	for (unsigned i = 0; i < lights.size(); i++)
	{
		std::stringstream ss;
		std::string index;
		ss << i;
		index = ss.str();
		GLuint dirLoc = glGetUniformLocation(program, ("lightDirs[" + index + "]").c_str());
		lightDirectionUniformLocations.push_back(dirLoc);

		GLuint colorLoc = glGetUniformLocation(program, ("lightColors[" + index + "]").c_str());
		lightColorUniformLocations.push_back(colorLoc);
	}
	*/
}

Shader::~Shader()
{
	for (unsigned i = 0; i < NUM_SHADERS; i++)
	{
		glDetachShader(program, shaders[i]);
		glDeleteShader(shaders[i]);
	}
	glDeleteProgram(program);
}

GLuint Shader::createShader(const std::string& shaderSource, GLenum shaderType)
{
	GLuint shader = glCreateShader(shaderType);
	if (shader == 0)
	{
		std::cerr << "Error: " << ((shaderType == GL_VERTEX_SHADER) ? "vertex" : "fragment") << " shader creation failed" << std::endl;
	}

	const GLchar* shaderSourceString = shaderSource.c_str();
	GLint shaderSourceStringLength = shaderSource.length();

	glShaderSource(shader, 1, &shaderSourceString, &shaderSourceStringLength);
	glCompileShader(shader);

	// check compile status
	GLint success = 0;
	glGetObjectParameterivARB(shader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		std::cerr << ((shaderType == GL_VERTEX_SHADER) ? "Vertex" : "Fragment") << " shader " << "compilation failed" << std::endl;
		GLint logSize = 0;
		glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &logSize);
		
		std::vector<GLchar> log(logSize);
		glGetShaderInfoLog(shader, logSize, &logSize, &log[0]);
		for (int i = 0; i < log.size(); i++)
		{
			std::cout << log[i];
		}
		std::cout << std::endl;
		glDeleteShader(shader);
		return NULL;
	}

	return shader;
}

std::string fileLoader(const std::string& fileName)
{
	std::ifstream file;
	std::string line;
	std::string ret;
	file.open(fileName);

	if (file.is_open())
	{
		while (file.good())
		{
			std::getline(file, line);
			ret.append(line + "\n");
		}
	}
	else
	{
		std::cerr << "Unable to open file: " << fileName << std::endl;
	}

	return ret;
}

void Shader::update(Camera& camera)
{
	glUniformMatrix4fv(uniforms[PROJECTION_UNIFORM], 1, GL_FALSE, &camera.getViewProjection()[0][0]);
	glUniform3f(uniforms[VIEW_POS_UNIFORM], camera.getPos().x, camera.getPos().y, camera.getPos().z);
	glUniform1i(newLightUniforms[NUM_LIGHTS_UNIFORM], lights.size());

	// send all of the light data to gpu
	for (unsigned i = 0; i < lights.size(); i++)
	{
		glUniform3f(lightDirectionUniformLocations[i], lights[i].getPosition().x, lights[i].getPosition().y, lights[i].getPosition().z);
		glUniform3f(lightColorUniformLocations[i], lights[i].getColor().r, lights[i].getColor().g, lights[i].getColor().b);
	}
}

void Shader::use()
{
	glUseProgram(program);
}

void Shader::pushLight(Light l)
{
	int i = lights.size();	// get the location of the last light
	lights.push_back(l);	// push the new light
	std::stringstream ss;
	std::string index;
	ss << i;				// convert the location into a string
	index = ss.str();
	GLuint dirLoc = glGetUniformLocation(program, ("lightDirs[" + index + "]").c_str());	// update uniform locations
	lightDirectionUniformLocations.push_back(dirLoc);

	GLuint colorLoc = glGetUniformLocation(program, ("lightColors[" + index + "]").c_str());
	lightColorUniformLocations.push_back(colorLoc);
}

void Shader::popLight(Light light)
{
	std::cerr << "popLight not yet tested" << std::endl;
	int i = lights.size();	// get the location of the last light
	for (std::vector<Light>::iterator it = lights.begin(); it < lights.end(); it++)
	{
		if (*it == light)
		{
			lights.erase(it);
			std::stringstream ss;
			std::string index;
			ss << i;				// convert the location into a string
			index = ss.str();
			GLuint dirLoc = glGetUniformLocation(program, ("lightDirs[" + index + "]").c_str());	// update uniform locations
			lightDirectionUniformLocations.push_back(dirLoc);

			GLuint colorLoc = glGetUniformLocation(program, ("lightColors[" + index + "]").c_str());
			lightColorUniformLocations.push_back(colorLoc);
		}
	}
}

void Shader::popLight()
{
	std::cerr << "popLight not yet tested" << std::endl;
	int i = lights.size();	// get the location of the last light
	lights.erase(lights.end());
	std::stringstream ss;
	std::string index;
	ss << i;				// convert the location into a string
	index = ss.str();
	GLuint dirLoc = glGetUniformLocation(program, ("lightDirs[" + index + "]").c_str());	// update uniform locations
	lightDirectionUniformLocations.push_back(dirLoc);

	GLuint colorLoc = glGetUniformLocation(program, ("lightColors[" + index + "]").c_str());
	lightColorUniformLocations.push_back(colorLoc);
}

void cleanUpShaders()
{
	delete Shaders::mainShader;
	delete Shaders::instancedShader;
}