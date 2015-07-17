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
#include "Entity.h"

#define ARRAY_SIZE(x) (sizeof(x) / sizeof((x)[0]))

int main(int argc, char **argv)
{
	Engine engine;

	engine.getTextureManager()->addTexture("brick.png");
	engine.getTextureManager()->addTexture("test.png");
	engine.getTextureManager()->addTexture("blue.png");
	engine.getTextureManager()->addTexture("white.png");

	engine.getShader()->pushLight(Light(glm::vec3(1.2f, 1.0f, 2.0f), glm::vec3(1.0, 1.0, 1.0)));
	engine.getShader()->pushLight(Light(glm::vec3(2.f, 1.f, -1.f)));

	std::vector<std::string> names;

	for (int i = 0; i < 100; i++)
	{
		std::stringstream ss;
		ss << i;
		std::string name = ss.str();
		names.push_back(name);
		Entity temp(engine, "cube.obj", name, "white.png");
		engine.addActor(temp);
		engine.getActor(name).moveTo(glm::vec3(i, cos(sin(i)), 1));
	}

	float counter = 0.0;
	while (engine.isRunning())
	{
		double lastTime = SDL_GetTicks();

		engine.render();

		for (int i = 0; i < names.size(); i++)
		{
			engine.getActor(names[i]).moveTo(glm::vec3(i, cos(sin(counter)), 1));
		}

		double deltaT = (SDL_GetTicks() - lastTime);
		const double fps = 60.f;
		if (deltaT < 1000 / fps)
		{
			int delayTime = 1000 / fps - deltaT;
			SDL_Delay(delayTime);
			//std::cout << delayTime << std::endl;
		}

		engine.handleEvents(deltaT);
		counter += 0.1;
	}

	return 0;
}