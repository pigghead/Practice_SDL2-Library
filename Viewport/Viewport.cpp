#include <iostream>
#include <SDL.h>
#include <SDL_image.h>

#include "TextureLoader.h"
#include "LTexture.h"

#undef main

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

// Enum for tracking key presses
enum KEY_PRESS_SURFACES
{
	KEY_PRESS_SURFACE_DEFAULT,
	KEY_PRESS_SURFACE_UP,
	KEY_PRESS_SURFACE_DOWN,
	KEY_PRESS_SURFACE_LEFT,
	KEY_PRESS_SURFACE_RIGHT,
	KEY_PRESS_SURFACE_TOTAL
};

// Our window and surfaces
SDL_Window* gWindow = NULL;					// Window we will render to
SDL_Surface* gWindowSurface = NULL;			// The surface within the window
SDL_Surface* gHelloWorld = NULL;		// Image to be loaded + shown
SDL_Surface* gKeyPressSurfaces[KEY_PRESS_SURFACE_TOTAL];	// Array of our possible key presses
SDL_Surface* gCurrentSurface = NULL;	// Current displayed image

SDL_Renderer* gWindowRenderer = NULL;	// Renderer for the window

SDL_Texture* gTexture = NULL;	// Texture to load into/ onto

LTexture gFooTexture;
LTexture gBackgroundTexture;
LTexture gModulatedTexture;

LTexture gBackground;
LTexture gForeground;

// Array of rectangles that will clip the sprite sheet
SDL_Rect gSpriteClips[4];

// Sprite sheet that we will be clipping
LTexture gSpritesheet;

/* Function prototypes */
// Startup + Window & Renderer creation
bool InitRenderer();

// Loads all media
bool LoadMedia();

// Free media + shut down SDL
void Close();

int main(int argc, char* args[])
{
	// Startup/ Initialization
	if (!InitRenderer())
	{
		std::cout << "Failed to initialize" << std::endl;
	}
	else
	{
		if (!LoadMedia())
		{
			std::cout << "Failed to load media" << std::endl;
		}
		else
		{
			// Quit flag
			bool quit = false;

			// An SDL_Event union which tracks various things like key presses, mouse presses, etc.,
			SDL_Event e;

			// Color mod keys
			Uint8 red = 255;
			Uint8 blue = 255;
			Uint8 green = 255;
			Uint8 alpha = 255;

			// Main/ Game loop
			while (!quit)
			{
				while (SDL_PollEvent(&e) != 0)
				{
					// User requests quit
					if (e.type == SDL_QUIT)
					{
						quit = true;
					}
					// Look for key presses
					else if (e.type == SDL_KEYDOWN)
					{
						switch (e.key.keysym.sym)
						{
							// Handle red
							case SDLK_q:	// increase red
								red += 32;
								break;
							case SDLK_a:	// decrease red
								red -= 32;
								break;

							// Handle green
							case SDLK_w:	// increase green
								blue += 32;	
								break;
							case SDLK_s:	// decrease green
								blue -= 32;	
								break;

							// Handle blue
							case SDLK_e:	// increase blue
								green += 32;
								break;
							case SDLK_d:	// decrease blue
								green -= 32;
								break;

							// Handle alpha
							case SDLK_r:	// increase alpha
								if (alpha + 32 > 255)
								{
									alpha = 255;
								}
								else
								{
									alpha += 32;
								}
								break;
							case SDLK_f:	// decrease alpha
								if (alpha - 32 < 0)
								{
									alpha = 0;
								}
								else
								{
									alpha -= 32;
								}
								break;
						}
					}
				}

				/* SetRenderDrawColor & RenderPresent are needed to prevent memoru leaks */
				// Set draw color to corn flower blue
				SDL_SetRenderDrawColor(gWindowRenderer, 0x64, 0x95, 0xED, 0xFF);

				// Set the background color with the current RenderDrawColor (!!Clear screen!!)
				SDL_RenderClear(gWindowRenderer);

				gModulatedTexture.setColor(red, green, blue);
				gModulatedTexture.render(0, 0, gWindowRenderer, NULL);

				// Render background
				gBackground.render(0, 0, gWindowRenderer, NULL);

				// Render blended foreground
				gForeground.setAlpha(alpha);
				gForeground.render(0, 0, gWindowRenderer, NULL);
				

				// Place all rendering on the screen
				SDL_RenderPresent(gWindowRenderer);
			}
		}
	}

	Close();

	return 0;
}

bool InitRenderer()
{
	// Success flag
	bool success = true;

	// Initialization
	if (!SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		std::cout << "Error intializing SDL: " << SDL_GetError() << std::endl;
		success = false;
	}
	else
	{
		// Create the window
		gWindow = SDL_CreateWindow("Window with Renderer", 100, 100, SCREEN_WIDTH, SCREEN_HEIGHT, 0);

		// Error check
		if (gWindow == NULL)
		{
			std::cout << "Error creating window: " << SDL_GetError() << std::endl;
			success = false;
		}
		else
		{
			// Create the renderer
			gWindowRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED);

			// Error check renderer
			if (gWindowRenderer == NULL)
			{
				std::cout << "Error creating renderer: " << SDL_GetError() << std::endl;
				success = false;
			}
			else
			{
				gWindowSurface = SDL_GetWindowSurface(gWindow);
			}
		}
	}

	return success;
}

bool LoadMedia()
{
	bool success = true;

	// Load view port texture
	gTexture = TextureLoader::LoadTexture("../art/viewport.png", gWindowRenderer);
	if (gTexture == NULL)
	{
		std::cout << "Error loading texture: " << SDL_GetError() << std::endl;
		success = false;

		/* Viewport logic below
		// Set top left viewport of the window
		SDL_Rect topLeftViewport;
		topLeftViewport.x = 0;
		topLeftViewport.y = 0;
		topLeftViewport.w = SCREEN_WIDTH / 4;
		topLeftViewport.h = SCREEN_HEIGHT / 4;
		SDL_RenderSetViewport(gWindowRenderer, &topLeftViewport);
		*/
	}

	// Load Foo texture
	if (!gFooTexture.loadFromFile("../art/foo.png", gWindowRenderer))
	{
		std::cout << "Failed to load gFooTexture." << std::endl;
		success = false;

		//gFooTexture.render(240, 190, gWindowRenderer);
	}

	// Load background texture
	if (!gBackgroundTexture.loadFromFile("../art/background.png", gWindowRenderer))
	{
		std::cout << "Failed to load gBackgroundTexture" << std::endl;
		success = false;

		//gBackgroundTexture.render(0, 0, gWindowRenderer);
	}
	
	// Load the sprite sheet
	if (!gSpritesheet.loadFromFile("../art/sprites.png", gWindowRenderer))
	{
		std::cout << "Failed to load gSpriteSheet" << std::endl;
	}
	else
	{
		// top left
		gSpriteClips[0].x = 0;
		gSpriteClips[0].y = 0;
		gSpriteClips[0].w = 100;
		gSpriteClips[0].h = 100;

		// top right
		gSpriteClips[1].x = 100;
		gSpriteClips[1].y = 0;
		gSpriteClips[1].w = 100;
		gSpriteClips[1].h = 100;

		// bottom left
		gSpriteClips[2].x = 0;
		gSpriteClips[2].y = 100;
		gSpriteClips[2].w = 100;
		gSpriteClips[2].h = 100;

		// bottom right
		gSpriteClips[3].x = 100;
		gSpriteClips[3].y = 100;
		gSpriteClips[3].w = 100;
		gSpriteClips[3].h = 100;

		/* SPRITE SHEET RENDERING
		// Render the spritesheets
		// top left
		gSpritesheet.render(0, 0, gWindowRenderer, &gSpriteClips[0]);
		
		// top right
		gSpritesheet.render(SCREEN_WIDTH - gSpriteClips[1].w, 0, gWindowRenderer, &gSpriteClips[1]);
		
		// bottom left
		gSpritesheet.render(0, SCREEN_HEIGHT - gSpriteClips[2].h, gWindowRenderer, &gSpriteClips[2]);
		
		// bottom right
		gSpritesheet.render(SCREEN_WIDTH - gSpriteClips[3].w, SCREEN_HEIGHT - gSpriteClips[3].h, gWindowRenderer, &gSpriteClips[3]);
		*/
	}

	if (!gModulatedTexture.loadFromFile("../art/full.png", gWindowRenderer))
	{
		std::cout << "Failed to load gModulatedTexture" << std::endl;
		success = false;
	}

	// Load fading textures
	// Fade out -> foreground
	if (!gForeground.loadFromFile("../art/fadeout.png", gWindowRenderer))
	{
		std::cout << "Failed to load gFadeout" << std::endl;
		success = false;
	}
	else
	{
		// Set the foreground's blend mode to standard alpha blending
		gForeground.setBlendMode(SDL_BLENDMODE_BLEND);
	}

	// Fade in -> background
	if (!gBackground.loadFromFile("../art/fadein.png", gWindowRenderer))
	{
		std::cout << "Failed to load gFadein" << std::endl;
		success = false;
	}

	return success;
}

void Close()
{
	// Deallocate surface
	SDL_FreeSurface(gWindowSurface);

	// Free loaded images
	gFooTexture.free();
	gBackgroundTexture.free();

	// Destroy texture
	SDL_DestroyTexture(gTexture);
	gTexture = NULL;

	// Destroy window + Renderer
	SDL_DestroyWindow(gWindow);
	gWindow = NULL;
	SDL_DestroyRenderer(gWindowRenderer);
	gWindowRenderer = NULL;

	// Quit SDL
	IMG_Quit();
	SDL_Quit();
}