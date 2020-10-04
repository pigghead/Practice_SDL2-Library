#include "OptimizedSurfaceLoader.h"

SDL_Surface* OptimizedSurfaceLoader::OptimizedLoadedSurface(std::string path, SDL_Surface* win)
{
	// optimized surface
	SDL_Surface* optimizedSurface = NULL;

	// loaded surface
	SDL_Surface* loadedSurface = SDL_LoadBMP(path.c_str());

	// Error check our loadedSurface
	if (loadedSurface == NULL)
	{
		std::cout << "Error loading surface: " << SDL_GetError() << std::endl;
	}
	else
	{
		// Convert our loadedSurface to 32bit (BMP are 24 bit by default)
		optimizedSurface = SDL_ConvertSurface(loadedSurface, win->format, 0);

		// Error check conversion
		if (optimizedSurface == NULL)
		{
			std::cout << "Error converting surface: " << SDL_GetError() << std::endl;
		}
	}

	// Free the surface
	SDL_FreeSurface(loadedSurface);

	return optimizedSurface;
}