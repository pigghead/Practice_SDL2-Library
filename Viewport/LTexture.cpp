#include "LTexture.h"

LTexture::LTexture()
{
	// Initialize
	tex = NULL;
	width = 0;
	height = 0;
};

LTexture::~LTexture()
{
	// Deallocate
	free();
};

bool LTexture::loadFromFile(std::string path, SDL_Renderer* ren)
{
	// Get rid of any preexisting texture
	free();

	SDL_Texture* newTexture = NULL;

	SDL_Surface* loadedSurface = IMG_Load(path.c_str());
	if (loadedSurface == NULL)
	{
		std::cout << "Error loading surface: " << IMG_GetError() << std::endl;
	}
	else
	{
		// Color key image
		SDL_SetColorKey(loadedSurface, SDL_TRUE, SDL_MapRGB(loadedSurface->format, 0, 0xFF, 0xFF));

		// Create tex from surface pixels
		newTexture = SDL_CreateTextureFromSurface(ren, loadedSurface);
		if (newTexture == NULL)
		{
			std::cout << "Error creating texture from surface: " << SDL_GetError() << std::endl;
		}
		else
		{
			// Get dimensions
			width = loadedSurface->w;
			height = loadedSurface->h;
		}

		SDL_FreeSurface(loadedSurface);
	}

	// Return success
	tex = newTexture;
	return tex != NULL;
};

void LTexture::free()
{
	if (tex != NULL)
	{
		SDL_DestroyTexture(tex);
		tex = NULL;
		width = 0;
		height = 0;
	}
};

void LTexture::setColor(Uint8 r, Uint8 g, Uint8 b)
{
	SDL_SetTextureColorMod(tex, r, g, b);
};

void LTexture::setBlendMode(SDL_BlendMode blending)
{
	SDL_SetTextureBlendMode(tex, blending);
};

void LTexture::setAlpha(Uint8 a)
{
	SDL_SetTextureAlphaMod(tex, a);
};

void LTexture::render(int x, int y, SDL_Renderer* ren, SDL_Rect* clip = NULL)
{
	// Set rendering space and render to screen
	SDL_Rect renderQuad = { x, y, width, height };

	// If a clip exists, retrieve its w and h
	if (clip != NULL)
	{
		renderQuad.w = clip->w;
		renderQuad.h = clip->h;
	}

	// Render to screen
	SDL_RenderCopy(ren, tex, clip, &renderQuad);
};

int LTexture::getHeight()
{
	return height;
};

int LTexture::getWidth()
{
	return width;
};