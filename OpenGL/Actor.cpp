#include "Actor.h"

Actor::Actor(const std::string& meshFileName, const std::string& textureFileName) :
	velocityX(0.f),
	velocityY(0.f),
	mesh(meshFileName, textureManager->getTexture(textureFileName), Shaders::mainShader->getProgram())
{
	mesh.getPosition().x = 4;
}