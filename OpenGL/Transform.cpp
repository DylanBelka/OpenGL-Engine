#include "Transform.h"

Transform::Transform(const glm::vec3& pos, const glm::vec3& rot, const glm::vec3& scale)
{
	position = pos;
	rotation = rot;
	this->scale = scale;
}

glm::mat4 Transform::getModel() const
{
	glm::mat4 viewMatrix = glm::translate(position);
	glm::mat4 rotXMatrix = glm::rotate(rotation.x, glm::vec3(1, 0, 0));
	glm::mat4 rotYMatrix = glm::rotate(rotation.y, glm::vec3(0, 1, 0));
	glm::mat4 rotZMatrix = glm::rotate(rotation.z, glm::vec3(0, 0, 1));
	glm::mat4 scaleMatrix = glm::scale(scale);

	glm::mat4 rotMatrix = rotZMatrix * rotYMatrix * rotXMatrix;
	return scaleMatrix * rotMatrix;
}

glm::mat4 Transform::getView() const
{
	return glm::translate(position);
}

glm::mat4 Transform::getModelView() const
{
	return getView() * getModel();
}
