#include "Actor.h"

Actor::Actor(Engine& e, const std::string& meshFileName, const std::string& actorName, const std::string& textureFileName) :
	velocityX(0.f),
	velocityY(0.f),
	name(actorName),
	mesh(meshFileName, e.getTextureManager()->getTexture(textureFileName), e.getShader()->getProgram())
{
	mesh.getPosition().x = 4;
}

Actor::Actor() :
	velocityX(0.f),
	velocityY(0.f),
	name("unassigned"),
	mesh("cube.obj", NULL, NULL)
{

}


void Actor::draw()
{
	mesh.draw();
}

void Actor::moveTo(glm::vec3& pos)
{
	mesh.getPosition() = pos;
}