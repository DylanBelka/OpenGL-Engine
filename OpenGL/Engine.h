#ifndef ENGINE_H
#define ENGINE_H

#include <map>
#include <vector>

#include "Shader.h"
#include "Display.h"
#include "TextureManager.h"
#include "Entity.h"
#include "Player.h"
#include "GUIObject.h"

class Engine
{
public:
	Engine();
	~Engine();

	void render();
	void handleEvents(double dt);
	bool isRunning() { return display->isOpen(); }

	void addActor(Entity& actor);
	void addGUIObject(GUIObject& o);

	TextureManager* getTextureManager() { return textureManager; }
	Shader* getShader() { return shader; }
	Shader* getInstancedShader() { return shader; }

	Entity& getEntity(const std::string& name) { return entities[name]; }

private:
	Display* display;
	TextureManager* textureManager;
	Shader* shader;
	Shader* instancedShader;
	Shader* guiShader;

	std::vector<GUIObject> guiObjects;

	Player* player;

	std::map<std::string, Entity> entities;
};

#endif