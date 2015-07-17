#include "Engine.h"

Engine::Engine()
{
	display = new Display(800, 600, "OpenGL");
	display->setClearColor(glm::vec3(0.0, 0.0, 0.0));

	textureManager = new TextureManager();
	shader = new Shader("shader");
	instancedShader = new Shader("instancedShader");
	player = new Player(glm::vec3(0.0, 0.0, -10.0), 70, (float)display->getWidth() / (float)display->getHeight(), .1, 1000.0);
}

Engine::~Engine()
{
	delete textureManager;
	delete display;
	delete shader;
	delete instancedShader;
	delete player;
}

void Engine::render()
{
	display->clear();

	shader->use();
	shader->update(*player->getCamera());

	for (std::map<std::string, Entity>::iterator it = entities.begin(); it != entities.end(); it++)
	{
		it->second.draw();
	}

	display->display();
}

void Engine::handleEvents(double dt)
{
	display->handleEvents(player->getCamera(), dt);
}

void Engine::addActor(Entity& actor)
{
	entities[actor.getName()] = actor;
}