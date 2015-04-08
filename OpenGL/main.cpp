#include <iostream>
#include <random>

#include <glew.h>
#include <GLFW\glfw3.h>
#include <glm/glm.hpp>
#include <SFML\Graphics.hpp>

#include "tiny_obj_loader.h"

#include "Display.h"
#include "Shader.h"
#include "BasicMesh.h"
#include "Camera.h"
#include "Texture.h"
#include "InstancedMesh.h"
#include "Light.h"
#include "CubeMap.h"

#define ARRAY_SIZE(x) (sizeof(x) / sizeof((x)[0]))

/* TODO:
Fix timer/ make better one
Create light class that has mesh
Create a lower poly sphere to use for stars - instanced
*/

/*
bool isCollision(BasicMesh a, BasicMesh b)
{
	if (abs(a.getPosition().x - b.getPosition().x) < a.getScale().x + b.getScale().x)
	{
		if (abs(a.getPosition().y - b.getPosition().y) < a.getScale().y + b.getScale().y)
		{
			if (abs(a.getPosition().z - b.getPosition().z) < a.getScale().z + b.getScale().z)
			{
				return true;
			}
		}
	}
	return false;
}
*/

static sf::Clock gameClock;

int main(int argc, char **argv)
{
	Display display(800, 600, "OpenGL");
	display.setClearColor(glm::vec3(0.0, 0.0, 0.0));

	Camera camera(glm::vec3(0.0, 0.0, -10.0), 70, (float)display.getWidth() / (float)display.getHeight(), .1, 1000.0);

	Shader shader("shader");
	Shader instancedShader("instancedShader");

	Texture texture("brick.png");
	Texture texture2("test.png");
	Texture blue("blue.png");
	Texture white("white.png");
	texture.bind();
	texture2.bind(1);
	blue.bind(2);
	white.bind(3);

	BasicMesh monkey("monkey.obj", texture.getTexture(), shader.getProgram());
	BasicMesh cube("cube.obj", white.getTexture(), shader.getProgram());
	BasicMesh cube2("cube.obj", texture.getTexture(), shader.getProgram());
	BasicMesh plane("plane.obj", texture.getTexture(), shader.getProgram());
	//BasicMesh sphere("sphere.obj", texture.getTexture(), shader.getProgram());
	BasicMesh sphere("spherelow.obj", white.getTexture(), shader.getProgram());

	shader.pushLight(glm::vec3(1.2f, 1.0f, 2.0f), glm::vec3(1.0, 1.0, 1.0));
	shader.pushLight(glm::vec3(2.f, 1.f, -1.f));
	instancedShader.pushLight(glm::vec3(1.2f, 1.0f, 2.0f), glm::vec3(1.0, 1.0, 1.0));
	instancedShader.pushLight(glm::vec3(2.f, 1.f, -1.f));

	const unsigned instancedDraws = 5000;

	std::srand(std::time(NULL));
	
	Transform t;
	std::vector<glm::mat4> positions;
	for (unsigned i = 0; i < instancedDraws; i++)
	{
		t.getPosition().x = rand() % 100 - 50;
		t.getPosition().y = rand() % 100 - 50;
		t.getPosition().z = rand() % 100 - 50;
		positions.push_back(t.getView());
	}
	
	InstancedMesh instancedCube("cube.obj", texture.getTexture(), instancedShader.getProgram(), instancedDraws, positions);

	plane.getPosition().y = -2;
	monkey.getPosition().x = -2;
	cube2.getPosition().x = 2;
	cube.getPosition().x = -2;
	sphere.getPosition().x = -.2f;
	sphere.getPosition().y = -1.0f;
	sphere.getPosition().z = 0.3f;

	std::cout << "." << sizeof(long long) << " bytes." << std::endl;
	int x;
	std::cout << "x: " << x << std::endl;
	float counter = 0.0;

	while (display.isOpen())
	{
		float lastTime = gameClock.restart().asSeconds();
		display.clear();
		
		instancedShader.use();
		instancedShader.update(camera);
		// InstancedMesh drawing goes here

		instancedCube.draw();

		shader.use();
		shader.update(camera);
		// BasicMesh drawing goes here

		//monkey.draw();
		//cube.draw();
		//cube2.draw();
		//plane.draw();
		//sphere.draw();
		shader.drawLights();

		if (cube2.intersects(cube))
		{
			std::cout << "collision detected" << std::endl;
		}

		display.display();
		float deltaT = gameClock.restart().asSeconds(); /* TODO: Add greater precision (asMicroSeconds) rather than asSeconds */

		if (1 / deltaT < 100)
		{
			std::cout << 1 / deltaT << std::endl;
		}

		//display.handleEvents(camera, cube2, deltaT - lastTime);
		display.handleEvents(camera, deltaT - lastTime, shader, instancedShader);
		counter += 0.001;
	}

	return 0;
}