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
#include "Actor.h"

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

	Actor a(engine, "monkey.obj", "a", "brick.png");
	engine.addActor(a);
	Actor b(engine, "cube.obj", "b", "white.png");
	engine.addActor(b);
	
	float counter = 0.0;
	while (engine.isRunning())
	{
		double lastTime = SDL_GetTicks();

		engine.render();

		engine.getActor("a").moveTo(glm::vec3(sin(counter), cos(counter), tan(counter)));

		double deltaT = (SDL_GetTicks() - lastTime) / 1000;
		const double fps = 60.f;
		if (deltaT < 1000 / fps)
		{
			SDL_Delay(1000 / fps - deltaT);
		}

		engine.handleEvents(deltaT);
		counter += 0.1;
	}

	return 0;
}