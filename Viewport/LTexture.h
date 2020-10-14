#pragma once
#include <string>
#include <SDL.h>
// Texture Wrapper
class LTexture
{
public:
	LTexture();
	~LTexture();

	bool loadFromFile(std::string path);

	// Deallocates texture
	void free();

	// renders texture at a certain point
	void render(int x, int y);

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

