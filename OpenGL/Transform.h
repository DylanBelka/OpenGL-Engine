#ifndef TRANSFORM_H
#define TRANSFORM_H

#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>

class Transform
{
public:
	Transform(const glm::vec3& pos = glm::vec3(), const glm::vec3& rot = glm::vec3(), const glm::vec3& scale = glm::vec3(1.0, 1.0, 1.0));

	// model and view matrix not including rotation
	glm::mat4 getModel() const;

	// just model matrix
	glm::mat4 getView() const;

	glm::mat4 getModelView() const;

	glm::vec3& getPosition() { return position; }
	glm::vec3& getRotation() { return rotation; }
	glm::vec3& getScale() { return scale; }

private:
	glm::vec3 position;
	glm::vec3 rotation;
	glm::vec3 scale;
};

#endif // TRANSFORM_H