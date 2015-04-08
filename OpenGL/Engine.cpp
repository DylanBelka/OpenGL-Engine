/*
#include "Engine.h"

Engine::Engine(std::string& title, unsigned width, unsigned height, std::string* shaderFileNames) :
	display(width, height, title),
	defaultShader(shaderFileNames[0]),
	instancedShader(shaderFileNames[1])
{
}

Engine::~Engine()
{

}

void Engine::render()
{
	display.clear();

	instancedShader.use();
	instancedShader.update(camera);
	for (InstancedMesh im : instancedMeshes)
		im.draw();

	defaultShader.use();
	defaultShader.update(camera);
	for (BasicMesh m : meshes)
		m.draw();

	display.display();
}
*/