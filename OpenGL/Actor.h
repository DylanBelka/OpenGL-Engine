#ifndef ACTOR_H
#define ACTOR_H

#include "BasicMesh.h"
#include "Texture.h"
#include "Shader.h"
#include "TextureManager.h"
#include "Engine.h"

#include <glm/glm.hpp>

class Actor
{
public:
	Actor(class Engine& e, const std::string& meshFileName, const std::string& textureFileName = "default.png");

	void draw();

	void moveTo(glm::vec3& pos);

private:
	BasicMesh mesh;
	double velocityX, velocityY;
};


#endif