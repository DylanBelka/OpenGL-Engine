#ifndef GUI_OBJECT_H
#define GUI_OBJECT_H

#include <string>
#include <vector>

#include <glew.h>
#include <glm/glm.hpp>

#include "Texture.h"

class GUIObject
{
public:
	GUIObject(std::vector<glm::vec2>& coords, GLuint texture, GLuint program);

	void draw();

private:
	enum Buffers
	{
		COORD_BUFFER,
		UV_BUFFER,
		ELEMENT_BUFFER,

		NUM_BUFFERS
	};

	GLuint vertexArrayID;
	GLuint vertexBufferIDs[NUM_BUFFERS];
	GLuint texture;
	std::vector<glm::vec2> coords; // x, y only -- z is a constant -1.0 so it is always drawn in front of everything else without the need for disabling depth testing
									// no MPV either so coordinates must be given in OpenGL coordinates rather than world coordinates
	GLsizei numCoords;
	std::vector<glm::vec2> uvs;
};

#endif