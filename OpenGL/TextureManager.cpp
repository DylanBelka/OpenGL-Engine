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
	Texture* txptr = textures[textureName];
	if (txptr == nullptr)			// if the texture does not already exist
	{								// make it and then search for it
		addTexture(textureName);	// there is a chance that a created texture is invalid for some reason
		getTexture(textureName);	// so instead get the texture by recursively calling this function until a valid one is created
	}
	else
	{
		return txptr->getTexture();
	}
}
