#ifndef ENGINE_H
#define ENGINE_H

#include "Shader.h"
#include "Display.h"

class Engine
{
public:
	Engine();
	~Engine();

	Display* getDisplay() { return display; }

private:
	Display* display;
};

#endif