#include "Engine.h"


Engine::Engine()
{
	display = new Display(800, 600, "OpenGL");
	display->setClearColor(glm::vec3(0.0, 0.0, 0.0));

	textureManager = new TextureManager();
	shader = new Shader("shader");
	instancedShader = new Shader("instancedShader");
	camera = new Camera(glm::vec3(0.0, 0.0, -10.0), 70, (float)display->getWidth() / (float)display->getHeight(), .1, 1000.0);
}

Engine::~Engine()
{
	delete textureManager;
	delete display;
	delete shader;
	delete instancedShader;
}


void Engine::render()
{
	display->clear();

	shader->use();
	shader->update(*camera);

	for (std::map<std::string, Actor>::iterator it = actors.begin(); it != actors.end(); it++)
	{
		it->second.draw();
	}

	display->display();
}

void Engine::handleEvents(double dt)
{
	display->handleEvents(camera, dt);
}

void Engine::addActor(Actor& actor)
{
	actors[actor.getName()] = actor;
}