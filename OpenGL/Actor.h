#ifndef ACTOR_H
#define ACTOR_H

#include "BasicMesh.h"
#include "Texture.h"
#include "Shader.h"
#include "TextureManager.h"

class Actor
{
public:
	Actor(const std::string& meshFileName, const std::string& textureFileName = "default.png");

private:
	BasicMesh mesh;
	double x, y;
};

#endif