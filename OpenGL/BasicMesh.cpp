#include "BasicMesh.h"

BasicMesh::BasicMesh(const std::string& fileName, GLuint texture, GLuint program, unsigned unit) :
	transform()
{
	std::vector<tinyobj::shape_t> shapes;
	std::vector<tinyobj::material_t> materials;

	std::string err = tinyobj::LoadObj(shapes, materials, fileName.c_str());
	if (!err.empty())
	{
		std::cerr << err << std::endl;
		return;
	}

	//textureUnit = unit;
	this->texture = texture;

	uniforms[MODEL_UNIFORM] = glGetUniformLocation(program, "model");
	uniforms[VIEW_UNIFORM] = glGetUniformLocation(program, "view");

	// convert tinyobj shapes into usable format
	std::vector<glm::vec3> positions;
	std::vector<glm::vec2> uvs;
	std::vector<glm::vec3> normals;
	std::vector<unsigned> indices;

	for (unsigned i = 0; i < shapes.size(); i++)
	{
		tinyobj::shape_t shape = shapes[i];
		for (unsigned j = 0; j < shape.mesh.positions.size(); j += 3)
		{
			positions.push_back(glm::vec3(shape.mesh.positions[j], shape.mesh.positions[j + 1], shape.mesh.positions[j + 2]));
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

	indicesCount = indices.size();

	glGenVertexArrays(1, &vertexArrayObject);
	glBindVertexArray(vertexArrayObject);
	glGenBuffers(NUM_BUFFERS, vertexArrayBuffers);

	glBindBuffer(GL_ARRAY_BUFFER, vertexArrayBuffers[POSITION_BUFFER]);
	glBufferData(GL_ARRAY_BUFFER, positions.size() * sizeof(glm::vec3), &positions[0], GL_STATIC_DRAW);

	glBindBuffer(GL_ARRAY_BUFFER, vertexArrayBuffers[UV_BUFFER]);
	glBufferData(GL_ARRAY_BUFFER, uvs.size() * sizeof(glm::vec2), &uvs[0], GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vertexArrayBuffers[INDEX_BUFFER]);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned), &indices[0], GL_STATIC_DRAW);

	glBindBuffer(GL_ARRAY_BUFFER, vertexArrayBuffers[NORMAL_BUFFER]);
	glBufferData(GL_ARRAY_BUFFER, normals.size() * sizeof(glm::vec3), &normals[0], GL_STATIC_DRAW);

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
}

BasicMesh::~BasicMesh()
{
	glDeleteVertexArrays(1, &vertexArrayObject);
}

void BasicMesh::draw()
{
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture);

	glBindBuffer(GL_ARRAY_BUFFER, vertexArrayBuffers[POSITION_BUFFER]);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

	glBindBuffer(GL_ARRAY_BUFFER, vertexArrayBuffers[UV_BUFFER]);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, 0);

	glBindBuffer(GL_ARRAY_BUFFER, vertexArrayBuffers[NORMAL_BUFFER]);
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, 0);

	// update uniforms
	glUniformMatrix4fv(uniforms[MODEL_UNIFORM], 1, GL_FALSE, &(transform.getModel()[0][0]));
	glUniformMatrix4fv(uniforms[VIEW_UNIFORM], 1, GL_FALSE, &(transform.getView()[0][0]));

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vertexArrayBuffers[INDEX_BUFFER]);
	glDrawElements(GL_TRIANGLES, indicesCount, GL_UNSIGNED_INT, 0);
}

bool BasicMesh::intersects(BasicMesh& other)
{
	if (abs(getPosition().x - other.getPosition().x) < getScale().x + other.getScale().x)
	{
		if (abs(getPosition().y - other.getPosition().y) < getScale().y + other.getScale().y)
		{
			if (abs(getPosition().z - other.getPosition().z) < getScale().z + other.getScale().z)
			{
				return true;
			}
		}
	}
	return false;
}