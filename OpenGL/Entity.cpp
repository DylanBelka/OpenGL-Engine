#include "Entity.h"

Entity::Entity(TextureManager& textureManager, Shader& shader, const std::string& meshFileName, const std::string& entityName, const std::string& textureFileName) :
	velocityX(0.f),
	velocityY(0.f),
	name(entityName),
	mesh(meshFileName, textureManager.getTexture(textureFileName),shader.getProgram())
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