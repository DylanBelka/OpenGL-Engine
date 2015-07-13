#include "TextureManager.h"

TextureManager::TextureManager()
{}

TextureManager::~TextureManager()
{
	for (std::map<std::string, Texture*>::iterator it = textures.begin(); it != textures.end(); it++)
	{
		delete it->second; // deallocate all texture pointers
	}
}

void TextureManager::addTexture(const std::string& textureFileName)
{
	Texture* tempTex = new Texture(textureFileName); // create textures as pointer to control lifetime
	textures[textureFileName] = tempTex;
}

GLuint TextureManager::getTexture(const std::string& textureName)
{
	return textures[textureName]->getTexture();
}
