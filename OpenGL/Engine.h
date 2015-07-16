#ifndef ENGINE_H
#define ENGINE_H

#include <map>

#include "Shader.h"
#include "Display.h"
#include "TextureManager.h"
#include "Actor.h"
#include "Player.h"

class Engine
{
public:
	Engine();
	~Engine();

	void render();
	void handleEvents(double dt);
	bool isRunning() { return display->isOpen(); }

	void addActor(Actor& actor);

	TextureManager* getTextureManager() { return textureManager; }
	Shader* getShader() { return shader; }
	Shader* getInstancedShader() { return shader; }

	Actor& getActor(const std::string& name) { return actors[name]; }

private:
	Display* display;
	TextureManager* textureManager;
	Shader* shader;
	Shader* instancedShader;

	Player* player;

	std::map<std::string, Actor> actors;
};

#endif