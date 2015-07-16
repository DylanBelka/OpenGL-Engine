#ifndef DISPLAY_H
#define DISPLAY_H

#define USE_SDL

#include <glew.h>
#include <glm/glm.hpp>
#include <glm/gtx/string_cast.hpp>

#include <SDL2/SDL.h>

#include <string>
#include <iostream>
#include <cmath>

#include "Camera.h"
#include "BasicMesh.h"
#include "Shader.h"
#include "Light.h"
#include "Mouse.h"

class Display
{
public:
	Display(const unsigned width, const unsigned height, const std::string& title);
	~Display();

	void display();
	void clear(float r, float g, float b);
	void clear();

	void handleEvents(Camera* camera, float deltaTime);

	void setClearColor(glm::vec3 color);

	unsigned getWidth() const { return width; }
	unsigned getHeight() const { return height; }

	bool isOpen() const { return windowOpen; }

	void resize(glm::vec2 newSize);

private:
	int width;
	int height;

	SDL_Window* window;
	SDL_GLContext glContext;

	bool windowOpen = true;
};

#endif // DISPLAY_H