#ifndef ENGINE_H
#define ENGINE_H

#include <vector>

#include "Shader.h"
#include "Display.h"
#include "TextureManager.h"
#include "Actor.h"

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

	Camera* getCamera() { return camera; }

private:
	Display* display;
	TextureManager* textureManager;
	Camera* camera;
	Shader* shader;
	Shader* instancedShader;

	std::vector<Actor> actors;
};

#endif