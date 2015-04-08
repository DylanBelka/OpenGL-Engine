#ifndef INSTANCEDMESH_H
#define INSTANCEDMESH_H

#include <cassert>
#include <vector>

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/string_cast.hpp>
#include <glew.h>

#include "tiny_obj_loader.h"
#include "Texture.h"
#include "Transform.h"

/*
* InstancedMesh allows for instance based rendering of a single model and texture
* The shader assigned to an InstancedMesh must be instanced as well
*/

class InstancedMesh
{
public:
	InstancedMesh(const std::string& fileName, GLuint texture, GLuint program, unsigned numDraws, std::vector<glm::mat4> transformMatrices);
	~InstancedMesh();

	void draw();

private:

	enum buffers
	{
		POSITION_BUFFER,
		UV_BUFFER,
		INDEX_BUFFER, // ebo
		NORMAL_BUFFER,
		MODEL_MATRIX_BUFFER,
		VIEW_MATRIX_BUFFER,

		NUM_BUFFERS
	};

	GLuint vertexArrayObject;
	GLuint vbos[NUM_BUFFERS];

	GLuint texture;

	unsigned indicesCount;
	unsigned drawCount;
	unsigned numDraws;
};

#endif // INSTANCEDMESH_H