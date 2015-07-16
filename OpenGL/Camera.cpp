#include "Camera.h"

Camera::Camera(const glm::vec3& pos, float fov, float aspect, float zNear, float zFar)
{
	perspective = glm::perspective(fov, aspect, zNear, zFar);
	position = pos;
	forward = glm::vec3(0, 0, 1);
	up = glm::vec3(0, 1, 0);
	angle = glm::vec2(0, 0);
	right = glm::vec3();
}

void Camera::init(const glm::vec3& pos, const float aspect, float fov, float zNear, float zFar)
{
	position = pos;
	perspective = glm::perspective(fov, aspect, zNear, zFar);
}

glm::mat4 Camera::getViewProjection() const
{
	return perspective * glm::lookAt(position, position + forward, up);
}
