#ifndef MOUSE_H
#define MOUSE_H

#include <SDL2/SDL.h>

namespace Mouse
{
	static float* angleX;
	static float* angleY;

	static const double sensitivity = .025;

	static int x;
	static int y;
}

#endif