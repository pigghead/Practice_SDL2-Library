#pragma once
#include <iostream>
#include <SDL.h>

class OptimizedSurfaceLoader
{
public:
	static SDL_Surface* OptimizedLoadedSurface(std::string path, SDL_Surface* win);
};

