#include "Player.h"

Player::Player(const glm::vec3& pos, const float aspect, float fov, float zNear, float zFar)
{
	camera = new Camera(pos, aspect, fov, zNear, zFar);
}

void Player::initCamera(const glm::vec3& pos, const float aspect, float fov, float zNear, float zFar)
{
	camera->init(pos, aspect, fov, zNear, zFar);
}
