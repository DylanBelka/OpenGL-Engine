#include "Engine.h"

Engine::Engine() 
{
	display = new Display(800, 600, "OpenGL");
	display->setClearColor(glm::vec3(0.0, 0.0, 0.0));

	textureManager = new TextureManager();
	shader = new Shader("shader");
	instancedShader = new Shader("instancedShader");
	guiShader = new Shader("GUIShader");
	player = new Player(glm::vec3(0.0, 0.0, -10.0), 70, (float)display->getWidth() / (float)display->getHeight(), .1, 1000.0);
}

Engine::~Engine()
{
	delete textureManager;
	delete display;
	delete shader;
	delete instancedShader;
	delete player;
	delete guiShader;
}

void Engine::update()
{

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

	guiShader->use();
	guiShader->update(*player->getCamera());

	for (GUIObject& o : guiObjects)
	{
		o.draw();
	}

	display->display();
}

void Engine::handleEvents(double dt)
{
	display->handleEvents(player, dt);
}

void Engine::addEntity(Entity& entity)
{
	entities[entity.getName()] = entity;
}

void Engine::addEntity(const std::string& meshFileName, const std::string& entityName, const std::string& textureFileName)
{
	Entity temp(*textureManager, *shader, meshFileName, entityName, textureFileName);
	entities[entityName] = temp;
}

void Engine::addGUIObject(GUIObject& o)
{
	guiObjects.push_back(o);
}