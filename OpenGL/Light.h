#ifndef LIGHT_H
#define LIGHT_H

#include <glm\glm.hpp>
#include <glew.h>

#include "BasicMesh.h"
#include "Texture.h"

class Light
{
public:
	Light(BasicMesh m, glm::vec3 pos, glm::vec3 color = glm::vec3(1.f, 1.f, 1.f));

	const glm::vec3 getPosition() { return position; }
	const glm::vec3 getColor() { return color; }

	void drawLight() { lightMesh.draw(); }

	bool operator==(Light& other);

private:
	glm::vec3 position;
	glm::vec3 color;
	BasicMesh lightMesh;
};

#endif // LIGHT_H