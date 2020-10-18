#pragma once
#include <iostream>
#include <string>
#include <SDL.h>
#include <SDL_image.h>
// Texture Wrapper
class LTexture
{
public:
	LTexture();
	~LTexture();

	bool loadFromFile(std::string path, SDL_Renderer* ren);

	// Deallocates texture
	void free();

	// Color modulation
	void setColor(Uint8 r, Uint8 g, Uint8 b);

	// Control color blending
	void setBlendMode(SDL_BlendMode blending);

	// Control alpha
	void setAlpha(Uint8 a);

	// renders texture at a certain point
	void render(int x, int y, SDL_Renderer* ren, SDL_Rect* clip);

	// get image dimensions
	int getWidth();
	int getHeight();

private:
	// The texture's hardware
	SDL_Texture* tex;

	// Image dimensions
	int width;
	int height;

};

