#include "InstancedMesh.h"

// offsets and size constants so they are not recalculated every draw call
static const GLsizei mat4Size = sizeof(glm::mat4);

static const GLsizei offsets[] =
{
	(sizeof(float) * 0), 
	(sizeof(float) * 4),
	(sizeof(float) * 8),
	(sizeof(float) * 12)
};

InstancedMesh::InstancedMesh(const std::string& fileName, GLuint texture, GLuint program, unsigned numDraws, std::vector<glm::mat4> positions) 
{
	assert(numDraws >= 1 && "Must be at least 1 draw"); // make sure the vectors can be populated and accessed

	std::vector<tinyobj::shape_t> shapes;
	std::vector<tinyobj::material_t> materials;

	std::string err = tinyobj::LoadObj(shapes, materials, fileName.c_str());
	if (!err.empty())
	{
		std::cerr << err << std::endl;
		return;
	}

	drawCount = 0;
	this->texture = texture;
	this->numDraws = numDraws;

	// convert tinyobj shapes into glm format
	std::vector<glm::vec3> poses;
	std::vector<glm::vec2> uvs;
	std::vector<glm::vec3> normals;
	std::vector<unsigned> indices;

	for (unsigned i = 0; i < shapes.size(); i++)
	{
		tinyobj::shape_t shape = shapes[i];
		drawCount += shape.mesh.positions.size();
		for (unsigned j = 0; j < shape.mesh.positions.size(); j += 3)
		{
			poses.push_back(glm::vec3(shape.mesh.positions[j], shape.mesh.positions[j + 1], shape.mesh.positions[j + 2]));
		}
		for (unsigned j = 0; j < shape.mesh.texcoords.size(); j += 2)
		{
			uvs.push_back(glm::vec2(shape.mesh.texcoords[j], shape.mesh.texcoords[j + 1]));
		}
		for (unsigned j = 0; j < shape.mesh.indices.size(); j++)
		{
			indices.push_back(shape.mesh.indices[j]);
		}
		for (unsigned j = 0; j < shape.mesh.normals.size(); j += 3)
		{
			normals.push_back(glm::vec3(shape.mesh.normals[j], shape.mesh.normals[j + 1], shape.mesh.normals[j + 2]));
		}
	}

	std::cout << poses.size() << std::endl;
	assert(uvs.size() > 0 && "Model has no uvs!");	// openGL doesnt like empty vectors
	assert(poses.size() > 0 && "Model has no positions!");
	assert(normals.size() > 0 && "Model has no normals!");
	assert(indices.size() > 0 && "Model has no indices (elements)!");
	
	Transform transform;

	std::vector<glm::mat4> modelMatrix;
	for (unsigned i = 0; i < numDraws; i++)
	{ 
		transform.getRotation().x = i;
		modelMatrix.push_back(transform.getModel());
	}
	
	indicesCount = indices.size();
 
	glGenVertexArrays(1, &vertexArrayObject);
	glBindVertexArray(vertexArrayObject);
	glGenBuffers(NUM_BUFFERS, vbos);

	glBindBuffer(GL_ARRAY_BUFFER, vbos[POSITION_BUFFER]);
	glBufferData(GL_ARRAY_BUFFER, poses.size() * sizeof(glm::vec3), &poses[0], GL_STATIC_DRAW);

	glBindBuffer(GL_ARRAY_BUFFER, vbos[UV_BUFFER]);
	glBufferData(GL_ARRAY_BUFFER, uvs.size() * sizeof(glm::vec2), &uvs[0], GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vbos[INDEX_BUFFER]);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned), &indices[0], GL_STATIC_DRAW);

	glBindBuffer(GL_ARRAY_BUFFER, vbos[NORMAL_BUFFER]);
	glBufferData(GL_ARRAY_BUFFER, normals.size() * sizeof(glm::vec3), &normals[0], GL_STATIC_DRAW);

	glBindBuffer(GL_ARRAY_BUFFER, vbos[MODEL_MATRIX_BUFFER]);
	glBufferData(GL_ARRAY_BUFFER, modelMatrix.size() * mat4Size, glm::value_ptr(modelMatrix[0]), GL_STATIC_DRAW);

	glBindBuffer(GL_ARRAY_BUFFER, vbos[VIEW_MATRIX_BUFFER]);
	glBufferData(GL_ARRAY_BUFFER, positions.size() * mat4Size, glm::value_ptr(positions[0]), GL_DYNAMIC_DRAW);

	//				 index, #data, type, norm?, skip, starting position
	// attrib 0  = position
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

	// attrib 1 = uvs
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, 0);

	// attrib 2 = normals
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, 0);

	// attrib 3, 4, 5, 6 = translation matrix
	glVertexAttribPointer(3, 4, GL_FLOAT, GL_FALSE, mat4Size, (GLvoid*) offsets[0]);
	glVertexAttribPointer(4, 4, GL_FLOAT, GL_FALSE, mat4Size, (GLvoid*) offsets[1]);
	glVertexAttribPointer(5, 4, GL_FLOAT, GL_FALSE, mat4Size, (GLvoid*) offsets[2]);
	glVertexAttribPointer(6, 4, GL_FLOAT, GL_FALSE, mat4Size, (GLvoid*) offsets[3]);

	glEnableVertexAttribArray(3);
	glEnableVertexAttribArray(4);
	glEnableVertexAttribArray(5);
	glEnableVertexAttribArray(6);

	// update the vertex in the shader every instance (model)
	glVertexAttribDivisor(3, 1);
	glVertexAttribDivisor(4, 1);
	glVertexAttribDivisor(5, 1);
	glVertexAttribDivisor(6, 1);

	// attrib 7, 9, 9, 10 = translation matrix
	glVertexAttribPointer(7, 4, GL_FLOAT, GL_FALSE, mat4Size, (GLvoid*) offsets[0]);
	glVertexAttribPointer(8, 4, GL_FLOAT, GL_FALSE, mat4Size, (GLvoid*) offsets[1]);
	glVertexAttribPointer(9, 4, GL_FLOAT, GL_FALSE, mat4Size, (GLvoid*) offsets[2]);
	glVertexAttribPointer(10, 4, GL_FLOAT, GL_FALSE, mat4Size, (GLvoid*) offsets[3]);

	glEnableVertexAttribArray(7);
	glEnableVertexAttribArray(8);
	glEnableVertexAttribArray(9);
	glEnableVertexAttribArray(10);

	// update the vertex in the shader every instance (model)
	glVertexAttribDivisor(7, 1);
	glVertexAttribDivisor(8, 1);
	glVertexAttribDivisor(9, 1);
	glVertexAttribDivisor(10, 1);
}

InstancedMesh::~InstancedMesh()
{
	glDeleteVertexArrays(1, &vertexArrayObject);
}

void InstancedMesh::draw()
{
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture);

	glBindBuffer(GL_ARRAY_BUFFER, vbos[POSITION_BUFFER]);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

	glBindBuffer(GL_ARRAY_BUFFER, vbos[UV_BUFFER]);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, 0);

	glBindBuffer(GL_ARRAY_BUFFER, vbos[NORMAL_BUFFER]);
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, 0);

	glBindBuffer(GL_ARRAY_BUFFER, vbos[MODEL_MATRIX_BUFFER]);
	glBindBuffer(GL_ARRAY_BUFFER, vbos[VIEW_MATRIX_BUFFER]);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vbos[INDEX_BUFFER]);
	glDrawElementsInstanced(GL_TRIANGLES, indicesCount, GL_UNSIGNED_INT, 0, numDraws);
}
