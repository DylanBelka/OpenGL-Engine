#ifndef CAMERA_H
#define CAMERA_H

#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>

class Camera
{
public:
	Camera(const glm::vec3& pos, float fov, float aspect, float zNear, float zFar)
	{
		perspective = glm::perspective(fov, aspect, zNear, zFar);
		position = pos;
		forward = glm::vec3(0, 0, 1);
		up = glm::vec3(0, 1, 0);
		angle = glm::vec2(0, 0);
		right = glm::vec3();
	}

	inline glm::mat4 getViewProjection() const
	{
		return perspective * glm::lookAt(position, position + forward, up); 
	}

	glm::vec3& getPos() { return position; }
	glm::vec3 getPosition() const { return position; }

	glm::vec3& getForward() { return forward; }
	glm::vec3& getUp() { return up; }

	glm::vec2& getAngle() { return angle; }
	void setAngle(glm::vec2& theta) { angle = theta; }
	glm::vec3& getRight() { return right; }

private:
	glm::mat4 perspective;
	glm::vec3 position;
	glm::vec3 forward;
	glm::vec3 up;
	glm::vec2 angle;
	glm::vec3 right;
};

#endif // CAMERA_H