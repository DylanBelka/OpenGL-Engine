#ifndef CAMERA_H
#define CAMERA_H

#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>

class Camera
{
public:
	Camera(const glm::vec3& pos, float fov, float aspect, float zNear, float zFar);
	Camera();

	void init(const glm::vec3& pos, const float aspect, float fov, float zNear, float zFar);

	glm::mat4 getViewProjection() const;

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