#include "Actor.h"

Actor::Actor(Engine& e, const std::string& meshFileName, const std::string& textureFileName) :
	velocityX(0.f),
	velocityY(0.f),
	mesh(meshFileName, e.getTextureManager()->getTexture(textureFileName), e.getShader()->getProgram())
{
	mesh.getPosition().x = 4;
}


void Actor::draw()
{
	mesh.draw();
}

void Actor::moveTo(glm::vec3& pos)
{
	mesh.getPosition() = pos;
}