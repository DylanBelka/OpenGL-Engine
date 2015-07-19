#ifndef ENTITY_H
#define ENTITY_H

#include "BasicMesh.h"
#include "TextureManager.h"
#include "Shader.h"

#include <glm/glm.hpp>

class Entity
{
public:
	Entity(TextureManager& textureManager, Shader& shader, const std::string& meshFileName, const std::string& entityName, const std::string& textureFileName);
	Entity(); // default constructor required for std::tuple which is required for std::map
	void draw();

	void moveTo(glm::vec3& pos);
	bool instersects(Entity& other) { return mesh.intersects(other.mesh); }

	const std::string& getName() const { return name; }

protected:
	BasicMesh mesh;
	double velocityX, velocityY;
	std::string name;
};

#endif