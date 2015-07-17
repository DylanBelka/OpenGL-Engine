#include "Entity.h"

Entity::Entity(Engine& e, const std::string& meshFileName, const std::string& actorName, const std::string& textureFileName) :
	velocityX(0.f),
	velocityY(0.f),
	name(actorName),
	mesh(meshFileName, e.getTextureManager()->getTexture(textureFileName), e.getShader()->getProgram())
{
	mesh.getPosition().x = 4;
}

Entity::Entity() :
	velocityX(0.f),
	velocityY(0.f),
	name("unassigned"),
	mesh("cube.obj", NULL, NULL)
{

}


void Entity::draw()
{
	mesh.draw();
}

void Entity::moveTo(glm::vec3& pos)
{
	mesh.getPosition() = pos;
}