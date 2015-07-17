#include "GUIObject.h"

GUIObject::GUIObject(std::vector<glm::vec2>& coords, GLuint texture, GLuint program) 
{
	const glm::vec2 uvs[] =
	{
		glm::vec2(0.0f, 0.0f),
		glm::vec2(1.0f, 0.0f),
		glm::vec2(1.0f, 1.0f),
		glm::vec2(0.0f, 1.0f),
	};

	const GLuint elements[] = 
	{
		0, 1, 2,
		2, 3, 0
	};

	this->coords = coords;
	this->texture = texture;
	glGenVertexArrays(1, &vertexArrayID);
	glBindVertexArray(vertexArrayID);
	glGenBuffers(NUM_BUFFERS, vertexBufferIDs);

	glBindBuffer(GL_ARRAY_BUFFER, vertexBufferIDs[COORD_BUFFER]);
	glBufferData(GL_ARRAY_BUFFER, coords.size() * sizeof(coords), &coords[0], GL_STATIC_DRAW);

	glBindBuffer(GL_ARRAY_BUFFER, vertexBufferIDs[UV_BUFFER]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(uvs), uvs, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vertexBufferIDs[ELEMENT_BUFFER]);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(elements), elements, GL_STATIC_DRAW);

	// coords
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, 0);

	// uvs
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, 0);
}

void GUIObject::draw()
{
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture);

	glBindBuffer(GL_ARRAY_BUFFER, vertexBufferIDs[COORD_BUFFER]);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, 0);

	glBindBuffer(GL_ARRAY_BUFFER, vertexBufferIDs[UV_BUFFER]);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, 0);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vertexBufferIDs[ELEMENT_BUFFER]);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}