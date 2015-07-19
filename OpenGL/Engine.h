#ifndef ENGINE_H
#define ENGINE_H

#include <map>
#include <vector>
#include <iostream>

#include "Shader.h"
#include "Display.h"
#include "TextureManager.h"
#include "Entity.h"
#include "Player.h"
#include "GUIObject.h"
#include "InstancedMesh.h"

class Engine
{
public:
	Engine();
	~Engine();

	void render();
	void update();
	void handleEvents(double dt);
	bool isRunning() const { return display->isOpen(); }

	void addEntity(Entity& entity);
	void addEntity(const std::string& meshFileName, const std::string& entityName, const std::string& textureFileName = "default.png");
	void addGUIObject(GUIObject& o);

	TextureManager* getTextureManager() { return textureManager; }
	Shader* getShader() { return shader; }
	Shader* getInstancedShader() { return shader; }

	Entity& getEntity(const std::string& name) { return entities[name]; }
	Player* getPlayer() { return player; }

private:
	Display* display;
	TextureManager* textureManager;
	Shader* shader;
	Shader* instancedShader;
	Shader* guiShader;

	std::vector<GUIObject> guiObjects;

	Player* player;

	std::map<std::string, Entity> entities;

	std::vector<int> keysPressed;
};

#endif