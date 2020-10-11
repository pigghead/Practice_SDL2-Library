#include "TextureLoader.h"

SDL_Texture* TextureLoader::LoadTexture(std::string path, SDL_Renderer* ren)
{
	// The final texture
	SDL_Texture* newTexture = NULL;

	// Load image at the specified path
	SDL_Surface* loadedSurface = IMG_Load(path.c_str());

	// Error check our loaded surface
	if (loadedSurface == NULL)
	{
		std::cout << "Error loading surface: " << SDL_GetError() << std::endl;
	}
	else
	{
		// Create a texture from the loaded surface
		newTexture = SDL_CreateTextureFromSurface(ren, loadedSurface);

		// Error check new texture
		if (newTexture == NULL)
		{
			std::cout << "Error creating texture: " << SDL_GetError() << std::endl;
		}

		// Free the old surface
		SDL_FreeSurface(loadedSurface);
	}

	return newTexture;
}