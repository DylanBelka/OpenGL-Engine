#ifndef PLAYER_H
#define PLAYER_H

#include <glm/glm.hpp>

#include "Camera.h"
#include "Transform.h"

class Player 
{
public:
	Player(const glm::vec3& pos, const float aspect, float fov, float zNear, float zFar);

	void initCamera(const glm::vec3& pos, const float aspect, float fov, float zNear, float zFar);

	Camera* getCamera() { return camera; }

private:
	Camera* camera;
	Transform transform;
};

#endif