#ifndef CUBE_MAP_H
#define CUBE_MAP_H

#include <cassert>
#include <string>
#include <iostream>

#include <soil/soil.h>
#include <glew.h>

class CubeMap
{
public:
	CubeMap(std::string& fileName);

private:
	GLuint texture;
};

#endif // CUBE_MAP_H