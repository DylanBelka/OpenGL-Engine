#ifndef DISPLAY_H
#define DISPLAY_H

#define USE_SDL

#include <glew.h>
#include <glm/glm.hpp>
#include <glm/gtx/string_cast.hpp>

#ifdef USE_SDL
#include <SDL2/SDL.h>
#else
#include <SFML/Window.hpp>
#include <SFML/OpenGL.hpp>
#endif	// USE_SDL

#include <string>
#include <iostream>
#include <cmath>

#include "Camera.h"
#include "BasicMesh.h"
#include "Shader.h"
#include "Light.h"

class Display
{
public:
	Display(const unsigned width, const unsigned height, const std::string& title);
	~Display();

	void display();
	void clear(float r, float g, float b);
	void clear();

	void handleEvents(Camera& camera, float deltaTime, Shader& shader, Shader& instancedShader);
	void handleEvents(Camera& camera, BasicMesh& mesh, float deltaTime);

	void setClearColor(glm::vec3 color);

	unsigned getWidth() const { return width; }
	unsigned getHeight() const { return height; }

#ifdef USE_SDL
	bool isOpen() const { return windowOpen; }
#else
	bool isOpen() { return window.isOpen(); }
#endif // USE_SDL

	void resize(glm::vec2 newSize);

private:
	int width;
	int height;

#ifdef USE_SDL
	SDL_Window* window;
	SDL_GLContext glContext;

	bool windowOpen = true;
#else
	sf::Window window;
#endif // USE_SDL
};

#endif // DISPLAY_H