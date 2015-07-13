#include <iostream>
#include <random>

<<<<<<< HEAD
#include <glm/glm.hpp>
=======
#include <glew.h>
#include <glm/glm.hpp>
//test
>>>>>>> 9785578d2f42e08521751f2fbba8e69a589d97f2

#include "tiny_obj_loader.h"

#include "Display.h"
#include "shader.h"
#include "BasicMesh.h"
#include "Camera.h"
#include "Texture.h"
#include "InstancedMesh.h"
#include "Light.h"
#include "Player.h"
#include "TextureManager.h"
//#include "CubeMap.h"

#define ARRAY_SIZE(x) (sizeof(x) / sizeof((x)[0]))

<<<<<<< HEAD
=======
/* TODO:
Fix timer/ make better one
Create light class that has mesh
Create a lower poly sphere to use for stars - instanced
*/

static sf::Clock gameClock;

>>>>>>> 9785578d2f42e08521751f2fbba8e69a589d97f2
int main(int argc, char **argv)
{
	Display display(800, 600, "OpenGL");
	display.setClearColor(glm::vec3(0.0, 0.0, 0.0));

	Camera camera(glm::vec3(0.0, 0.0, -10.0), 70, (float)display.getWidth() / (float)display.getHeight(), .1, 1000.0);

	Shaders::mainShader = new Shader("shader");
	Shaders::instancedShader = new Shader("instancedShader");

	textureManager = new TextureManager();

	textureManager->addTexture("brick.png");
	textureManager->addTexture("test.png");
	textureManager->addTexture("blue.png");
	textureManager->addTexture("white.png");

	Texture texture("brick.png");
	Texture texture2("test.png");
	// Texture blue("blue.png");
	// Texture white("white.png");
	//texture.bind();
	//texture2.bind(1);
	//blue.bind(2);
	//white.bind(3);

	Player p;

	//BasicMesh monkey("monkey.obj", texture.getTexture(), Shaders::mainShader->getProgram());
	//BasicMesh cube("cube.obj", white.getTexture(), Shaders::mainShader->getProgram());
	//BasicMesh cube2("cube.obj", texture.getTexture(), Shaders::mainShader->getProgram());
	//BasicMesh plane("plane.obj", texture.getTexture(), Shaders::mainShader->getProgram());
	////BasicMesh sphere("sphere.obj", texture.getTexture(), Shaders::mainShader->getProgram());
	//BasicMesh sphere("spherelow.obj", white.getTexture(), Shaders::mainShader->getProgram());

	BasicMesh monkey("monkey.obj", textureManager->getTexture("brick.png"), Shaders::mainShader->getProgram());
	BasicMesh cube("cube.obj", textureManager->getTexture("white.png"), Shaders::mainShader->getProgram());
	BasicMesh cube2("cube.obj", textureManager->getTexture("brick.png"), Shaders::mainShader->getProgram());
	BasicMesh plane("plane.obj", textureManager->getTexture("brick.png"), Shaders::mainShader->getProgram());
	//BasicMesh sphere("sphere.obj", texture.getTexture(), Shaders::mainShader->getProgram());
	BasicMesh sphere("spherelow.obj", textureManager->getTexture("white.png"), Shaders::mainShader->getProgram());

	Shaders::mainShader->pushLight(glm::vec3(1.2f, 1.0f, 2.0f), glm::vec3(1.0, 1.0, 1.0));
	Shaders::mainShader->pushLight(glm::vec3(2.f, 1.f, -1.f));
	Shaders::instancedShader->pushLight(glm::vec3(1.2f, 1.0f, 2.0f), glm::vec3(1.0, 1.0, 1.0));
	Shaders::instancedShader->pushLight(glm::vec3(2.f, 1.f, -1.f));
	
	const unsigned instancedDraws = 5000;

	std::srand(SDL_GetTicks());
	
	Transform t;
	std::vector<glm::mat4> positions;
	for (unsigned i = 0; i < instancedDraws; i++)
	{
		t.getPosition().x = rand() % 100 - 50;
		t.getPosition().y = rand() % 100 - 50;
		t.getPosition().z = rand() % 100 - 50;
		positions.push_back(t.getView());
	}
	
	InstancedMesh instancedCube("cube.obj", textureManager->getTexture("brick.png"), Shaders::instancedShader->getProgram(), instancedDraws, positions);
	
	plane.getPosition().y = -2;
	monkey.getPosition().x = -2;
	cube2.getPosition().x = 2;
	cube.getPosition().x = -2;
	sphere.getPosition().x = -.2f;
	sphere.getPosition().y = -1.0f;
	sphere.getPosition().z = 0.3f;

	std::cout << "." << sizeof(long long) << " bytes." << std::endl;
	
	float counter = 0.0;
	while (display.isOpen())
	{
		double lastTime = SDL_GetTicks();
		display.clear();
		
		Shaders::instancedShader->use();
		Shaders::instancedShader->update(camera);
		// InstancedMesh drawing goes here

		instancedCube.draw();

		Shaders::mainShader->use();
		Shaders::mainShader->update(camera);
		// BasicMesh drawing goes here

		monkey.draw();
		cube.draw();
		cube2.draw();
		plane.draw();
		sphere.draw();
		Shaders::mainShader->drawLights();

		display.display();

		double deltaT = (SDL_GetTicks() - lastTime) / 1000;
		const double fps = 60.f; 
		if (deltaT < 1000 / fps)
		{
			SDL_Delay(1000 / fps - deltaT);
		}

		//display.handleEvents(camera, cube2, deltaT);
		display.handleEvents(camera, deltaT);
		counter += 0.001;
	}

	cleanUpShaders();

	return 0;
}