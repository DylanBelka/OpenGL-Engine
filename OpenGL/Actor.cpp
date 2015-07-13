#include "Actor.h"

Actor::Actor(const std::string& meshFileName, const std::string& textureFileName) :
	x(0.f),
	y(0.f),
	mesh(meshFileName, textureManager->getTexture("white.png"), Shaders::mainShader->getProgram())
{

}