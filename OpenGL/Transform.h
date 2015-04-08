#ifndef TRANSFORM_H
#define TRANSFORM_H

#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>

class Transform
{
public:
	Transform(const glm::vec3& pos = glm::vec3(), const glm::vec3& rot = glm::vec3(), const glm::vec3& scale = glm::vec3(1.0, 1.0, 1.0))
	{
		position = pos;
		rotation = rot;
		this->scale = scale;
	}

	// model and view matrix not including rotation
	inline glm::mat4 getModel() const
	{
		glm::mat4 viewMatrix = glm::translate(position);
		glm::mat4 rotXMatrix = glm::rotate(rotation.x, glm::vec3(1, 0, 0));
		glm::mat4 rotYMatrix = glm::rotate(rotation.y, glm::vec3(0, 1, 0));
		glm::mat4 rotZMatrix = glm::rotate(rotation.z, glm::vec3(0, 0, 1));
		glm::mat4 scaleMatrix = glm::scale(scale);

		glm::mat4 rotMatrix = rotZMatrix * rotYMatrix * rotXMatrix;
		return scaleMatrix * rotMatrix;
	}

	// just model matrix
	inline glm::mat4 getView() const
	{
		return glm::translate(position);
	}

	inline glm::mat4 getModelView() const
	{
		return getView() * getModel();
	}

	glm::vec3& getPosition() { return position; }
	glm::vec3& getRotation() { return rotation; }
	glm::vec3& getScale() { return scale; }

private:
	glm::vec3 position;
	glm::vec3 rotation;
	glm::vec3 scale;
};

typedef Transform Position;

#endif // TRANSFORM_H