#include <iostream>
#include <random>

#include <glm/glm.hpp>
#include <glew.h>
#include <glm/glm.hpp>

#include "Display.h"
#include "shader.h"
#include "BasicMesh.h"
#include "Camera.h"
#include "Texture.h"
#include "Light.h"
#include "Player.h"
#include "TextureManager.h"
#include "Engine.h"

#define ARRAY_SIZE(x) (sizeof(x) / sizeof((x)[0]))

int main(int argc, char **argv)
{
	Display display(800, 600, "OpenGL");
	display.setClearColor(glm::vec3(0.0, 0.0, 0.0));

	Camera camera(glm::vec3(0.0, 0.0, -10.0), 70, (float)display.getWidth() / (float)display.getHeight(), .1, 1000.0);

	Shaders::mainShader = new Shader("shader");
	Shaders::instancedShader = new Shader("instancedShader");

	textureManager = new TextureManager();

	textureManager->addTexture("brick.png");
	textureManager->addTexture("test.png");
	textureManager->addTexture("blue.png");
	textureManager->addTexture("white.png");

	BasicMesh monkey("monkey.obj", textureManager->getTexture("brick.png"), Shaders::mainShader->getProgram());
	BasicMesh cube("cube.obj", textureManager->getTexture("white.png"), Shaders::mainShader->getProgram());
	BasicMesh cube2("cube.obj", textureManager->getTexture("brick.png"), Shaders::mainShader->getProgram());
	BasicMesh plane("plane.obj", textureManager->getTexture("brick.png"), Shaders::mainShader->getProgram());
	//BasicMesh sphere("sphere.obj", texture.getTexture(), Shaders::mainShader->getProgram());
	BasicMesh sphere("spherelow.obj", textureManager->getTexture("white.png"), Shaders::mainShader->getProgram());

	Shaders::mainShader->pushLight(Light(glm::vec3(1.2f, 1.0f, 2.0f), glm::vec3(1.0, 1.0, 1.0)));
	Shaders::mainShader->pushLight(Light(glm::vec3(2.f, 1.f, -1.f)));

	std::cout << "starting" << std::endl;
	
	float counter = 0.0;
	while (display.isOpen())
	{
		double lastTime = SDL_GetTicks();
		display.clear();

		Shaders::mainShader->use();
		Shaders::mainShader->update(camera);
		// BasicMesh drawing goes here

		monkey.draw();
		cube.draw();
		cube2.draw();
		plane.draw();
		sphere.draw();

		display.display();

		double deltaT = (SDL_GetTicks() - lastTime) / 1000;
		const double fps = 60.f;
		if (deltaT < 1000 / fps)
		{
			SDL_Delay(1000 / fps - deltaT);
		}

		//display.handleEvents(camera, cube2, deltaT);
		display.handleEvents(camera, deltaT);
		counter += 0.001;
	}

	cleanUpShaders();

	return 0;
}