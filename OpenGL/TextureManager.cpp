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
	if (txptr == nullptr)			// if the texture does not already exist, create it
	{
		addTexture(textureName);
		txptr = textures[textureName];
		if (txptr == nullptr)		// make sure that the created texture was created succesfully
		{
			std::cerr << "Texture " << textureName << " was not found and could not be created" << std::endl;
			return 0;
		}
	}
	return txptr->getHandle();
}
