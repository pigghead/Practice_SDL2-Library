#pragma once
#include <iostream>
#include <SDL.h>
#include <SDL_image.h>

class TextureLoader
{
public:
	static SDL_Texture* LoadTexture(std::string path, SDL_Renderer* ren);
};

