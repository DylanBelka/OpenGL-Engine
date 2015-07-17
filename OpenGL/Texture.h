#ifndef TEXTURE_H
#define TEXTURE_H

#include <cassert>
#include <string>
#include <iostream>

#include <soil/soil.h>
#include <glew.h>

/*
	A wrapper class for an OpenGL texture that performs loading and deletion of the texture
	All textures are stored in an std::map in the TextureManager class
*/

class Texture
{
public:
	Texture(const std::string& fileName, bool invertY)
	{
		if (invertY)
		{
			textureHandle = SOIL_load_OGL_texture(fileName.c_str(), SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT);
		}
		else  // GUI objects do not like inverted y
		{
			textureHandle = SOIL_load_OGL_texture(fileName.c_str(), SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT);
		}
		if (textureHandle == NULL)
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
		textureHandle = 0;
	}

	~Texture()
	{
		glDeleteTextures(1, &textureHandle);
	}

	GLuint getHandle() { return textureHandle; }

private:
	void bind(unsigned unit = 0) const
	{
		assert(unit <= 31 && unit >= 0);
		glActiveTexture(GL_TEXTURE0 + unit);
		glBindTexture(GL_TEXTURE_2D, textureHandle);
	}

	GLuint textureHandle;
};

#endif // TEXTURE_H