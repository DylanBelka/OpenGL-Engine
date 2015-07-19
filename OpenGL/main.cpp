#include <iostream>
#include <random>
#include <ctime>

#include <glm/glm.hpp>
#include <glew.h>
#include <glm/glm.hpp>

#include <glm/gtx/string_cast.hpp>

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
#include "GUIObject.h"
#include "InstancedMesh.h"
#include "Light.h"

#define ARRAY_SIZE(x) (sizeof(x) / sizeof((x)[0]))

int main(int argc, char **argv)
{
	Engine engine;

	engine.getTextureManager()->addTexture("brick.png");
	engine.getTextureManager()->addTexture("test.png");
	engine.getTextureManager()->addTexture("blue.png");
	engine.getTextureManager()->addTexture("white.png");
	engine.getTextureManager()->addTexture("guiTest.png", false);

	//engine.getShader()->pushLight(Light(glm::vec3(1.2f, 1.0f, 2.0f), glm::vec3(1.0, 1.0, 1.0)));
	//engine.getShader()->pushLight(Light(glm::vec3(2.f, 1.0f, -1.0f), glm::vec3(0.5, 0.0, 0.0)));
	//engine.getShader()->pushLight(Light(glm::vec3(3.0, 10.0, 10.0f), glm::vec3(1.0, 1.0, 1.0)));

	std::vector<std::string> names;

	srand(time(NULL));

	std::stringstream ss;
	std::string texture = "";

	const int numCubes = 0;

	for (int i = 0; i < numCubes; i++)
	{
		for (int j = 0; j < numCubes; j++)
		{
			float y = rand() % 3;

			ss << i;
			std::string name = ss.str();
			ss.flush();
			names.push_back(name);
			int x = (int)(rand() % 100);

			if (x % 3 == 0)
			{
				texture = "blue.png";
			}
			else if (x % 5 == 0)
			{
				texture = "test.png";
			}
			else
			{
				texture = "white.png";
			}

			engine.addEntity("cube.obj", name, texture);
			engine.getEntity(name).moveTo(glm::vec3(i * 2, y * 2, j * 2));
		}
	}

	//engine.addEntity("spherelow.obj", "test", "brick.png");
	//engine.addEntity("spherelow.obj", "test2", "brick.png");
	//engine.addEntity("spherelow.obj", "tes3", "brick.png");

	//engine.getEntity("test").moveTo(glm::vec3(1.2f, 1.0f, 2.0f));
	//engine.getEntity("test2").moveTo(glm::vec3(2.f, 1.0f, -1.0f));
	//engine.getEntity("test3").moveTo(glm::vec3(3.0, 10.0, 10.0f));

	engine.addEntity("cube.obj", "cube", "brick.png");
	engine.getEntity("cube").moveTo(glm::vec3(5.0f, 3.0f, 3.0f));
	engine.getShader()->pushLight(Light(glm::vec3(5.0f, 4.0f, 3.0f)));

	float counter = 0.0;

	const int ticksPerSecond = 120;
	const double skipTicks = ticksPerSecond / 1000.f;
	const int maxFrameSkip = 5;

	double nextGameTick = SDL_GetTicks();
	int loops;

	while (engine.isRunning())
	{
		loops = 0;
		while (SDL_GetTicks() > nextGameTick && loops < maxFrameSkip)
		{
			engine.update();
			engine.handleEvents(1.0);
			nextGameTick += skipTicks;
			loops++;
		}

		engine.render();
	}

	return 0;
}

/*
double lastTime = SDL_GetTicks();

engine.render();
engine.update();

double deltaT = (SDL_GetTicks() - lastTime);
const double fps = 60.f;
if (deltaT < 1000 / fps)
{
int delayTime = 1000 / fps - deltaT;
SDL_Delay(delayTime);
//std::cout << delayTime << std::endl;
}

std::cout << deltaT * 60 << std::endl;

engine.handleEvents(deltaT);
counter += 0.1;
*/

/*	
unsigned start = SDL_GetTicks() * 1000;
#define getSeconds() ((SDL_GetTicks() * 1000) - start)
	const double timePerFrameSeconds = (1.f / 60.f) * 1000.f;
	const double timePerFrameMillis = timePerFrameSeconds / 1000.f;
	unsigned long timeSinceLastUpdate = 0;
	while (engine.isRunning())
	{
		engine.handleEvents(1.0);
		timeSinceLastUpdate += getSeconds();
		while (timeSinceLastUpdate > timePerFrameSeconds)
		{
			timeSinceLastUpdate -= timePerFrameSeconds;
			//engine.handleEvents(timePerFrameMillis);
			//engine.update();
		}
		timeSinceLastUpdate = 0;
		engine.handleEvents(timePerFrameMillis);

		engine.render();
	}
*/