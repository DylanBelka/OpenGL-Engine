#ifndef BASIC_MESH_H
#define BASIC_MESH_H

#include <iostream>
#include <cassert>
#include <vector>

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <glew.h>

#include "tiny_obj_loader.h"
#include "Transform.h"

class BasicMesh
{
public:
	BasicMesh(const std::string& fileName, GLuint texture, GLuint program, unsigned unit = 0);
	~BasicMesh();

	void draw();

	bool intersects(BasicMesh& other);

	friend class Entity;	// allow the entity class to manipulate positional data

protected:
	Transform &getTransform() { return transform; }
	glm::vec3 &getPosition() { return transform.getPosition(); }
	glm::vec3 &getScale() { return transform.getScale(); }

private:
	enum buffers
	{
		POSITION_BUFFER,
		UV_BUFFER,
		INDEX_BUFFER, // ebo
		NORMAL_BUFFER,

		NUM_BUFFERS
	};
	
	enum uniforms
	{
		MODEL_UNIFORM,
		VIEW_UNIFORM,

		NUM_UNIFORMS
	};

	Transform transform;

	GLuint vertexArrayObject;
	GLuint vertexArrayBuffers[NUM_BUFFERS];

	GLuint uniforms[NUM_UNIFORMS];

	GLuint texture;

	unsigned indicesCount;
};

#endif // BASIC_MESH_H