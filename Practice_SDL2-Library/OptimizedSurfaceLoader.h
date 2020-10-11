#pragma once
#include <iostream>
#include <SDL.h>

class OptimizedSurfaceLoader
{
public:
	// Optimized loading for BMPs; Does not utilize SDL_image
	static SDL_Surface* OptimizedLoadedSurface(std::string path, SDL_Surface* win);

	// Optimized loading for PNGs; Utilizes SDL_image
	static SDL_Surface* OptimizedLoadedPNG(std::string path, SDL_Surface* win);
};

