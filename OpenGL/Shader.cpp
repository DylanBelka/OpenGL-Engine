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
		return;
	}
	
	uniforms[PROJECTION_UNIFORM] = glGetUniformLocation(program, "projection");
	uniforms[TEX_SAMPLER_UNIFORM] = glGetUniformLocation(program, "tex");
	numLightsUniform = glGetUniformLocation(program, "numLights");
	uniforms[VIEW_POS_UNIFORM] = glGetUniformLocation(program, "viewPos");
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
	glUniform3f(uniforms[VIEW_POS_UNIFORM], camera.getPosition().x, camera.getPosition().y, camera.getPosition().z);
	glUniform1i(numLightsUniform, lights.size()); 

	// send all of the light data to gpu
	for (unsigned i = 0; i < lights.size(); i++)
	{
		glUniform3f(lightPosUniformLocations[i], lights[i].getPosition().x, lights[i].getPosition().y, lights[i].getPosition().z);
		glUniform3f(lightColorUniformLocations[i], lights[i].getColor().r, lights[i].getColor().g, lights[i].getColor().b);
	}
}

void Shader::use()
{
	glUseProgram(program);
}

void Shader::pushLight(Light l)
{
	int i = lights.size();		// get the location of the next light
	if (i < MAX_LIGHTS)			// hard constant of 32 max lights
	{
		lights.push_back(l);	// add the new light to the lights vector
		std::stringstream ss;
		std::string index;
		ss << i;				// convert the location into a string
		index = ss.str();
		// get uniforms and add them to their vectors
		GLuint dirLoc = glGetUniformLocation(program, ("lightPos[" + index + "]").c_str());	// update uniform locations
		lightPosUniformLocations.push_back(dirLoc);

		GLuint colorLoc = glGetUniformLocation(program, ("lightColors[" + index + "]").c_str());
		lightColorUniformLocations.push_back(colorLoc);
	}
}