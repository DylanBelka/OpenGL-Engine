#ifndef TEXTURE_H
#define TEXTURE_H

#include <cassert>
#include <string>
#include <iostream>

#include <soil/soil.h>
#include <glew.h>

class Texture
{
public:
	Texture(const std::string& fileName)
	{
		texture = SOIL_load_OGL_texture(fileName.c_str(), SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT);
		if (texture == NULL)
		{
			std::cerr << "SOIL loading error " << SOIL_last_result();
			if (SOIL_last_result() == "Unable to open file")
			{
				std::cout << ": " << fileName;
			}
			std::cout << std::endl;
		}
	}

	Texture()
	{
		texture = 0;
	}

	~Texture()
	{
		glDeleteTextures(1, &texture);
	}

	GLuint getTexture() { return texture; }

private:
	void bind(unsigned unit = 0) const
	{
		assert(unit <= 31 && unit >= 0);
		glActiveTexture(GL_TEXTURE0 + unit);
		glBindTexture(GL_TEXTURE_2D, texture);
	}

	GLuint texture;
};

#endif // TEXTURE_H