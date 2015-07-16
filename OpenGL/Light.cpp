#include "Light.h"

Light::Light(glm::vec3 pos, glm::vec3 color)
{
	position = pos;
	this->color = color;
}

bool Light::operator==(Light& other)
{
	return
		getPosition().x == other.getPosition().x &&
		getPosition().y == other.getPosition().y &&
		getPosition().z == other.getPosition().z &&
		getColor().r == other.getColor().r &&
		getColor().b == other.getColor().g &&
		getColor().g == other.getColor().b;
}