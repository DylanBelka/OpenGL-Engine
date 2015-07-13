#ifndef TEXTURE_MANAGER_H
#define TEXTURE_MANAGER_H

#include <map>
#include <glew.h>

#include "Texture.h"

class TextureManager
{
public:
	TextureManager();
	~TextureManager();

	void addTexture(const std::string& textureFileName);

	GLuint getTexture(const std::string& textureName);

private:
	std::map<std::string, Texture*> textures;
	TextureManager(TextureManager const&) = delete;
	void operator=(TextureManager const&) = delete;
};

static TextureManager* textureManager;

#endif
