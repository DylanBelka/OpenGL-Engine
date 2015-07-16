#ifndef ACTOR_H
#define ACTOR_H

#include "BasicMesh.h"
#include "Engine.h"

#include <glm/glm.hpp>

class Actor
{
public:
	Actor(class Engine& e, const std::string& meshFileName, const std::string& actorName, const std::string& textureFileName = "default.png");
	Actor(); // default constructor required for std::tuple which is required for std::map
	void draw();

	void moveTo(glm::vec3& pos);

	const std::string& getName() const { return name; }

protected:
	BasicMesh mesh;
	double velocityX, velocityY;
	std::string name;
};

#endif