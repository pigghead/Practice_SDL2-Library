#include <iostream>
#include <SDL.h>
#include <SDL_image.h>

#include "LTexture.h"

#undef main

// SCREEN CONSTANTS
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

// BUTTON CONSTANTS
const int BUTTON_WIDTH = 300;
const int BUTTON_HEIGHT = 200;
const int TOTAL_BUTTONS = 4;

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

// Enum for button states
enum LButtonSprite
{
	BUTTON_SPRITE_MOUSE_OUT = 0,
	BUTTON_SPRITE_MOUSE_OVER_MOTION = 1,
	BUTTON_SPRITE_MOUSE_DOWN = 2,
	BUTTON_SPRITE_MOUSE_UP = 3,
	BUTTON_SPRITE_MOUSE_TOTAL = 4
};

// Our window and surfaces
SDL_Window* gWindow = NULL;					// Window we will render to
SDL_Surface* gWindowSurface = NULL;			// The surface within the window
SDL_Surface* gKeyPressSurfaces[KEY_PRESS_SURFACE_TOTAL];	// Array of our possible key presses

SDL_Renderer* gWindowRenderer = NULL;	// Renderer for the window

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

				}
				/* SetRenderDrawColor & RenderPresent are needed to prevent memoru leaks */
				// Set draw color to corn flower blue
				SDL_SetRenderDrawColor(gWindowRenderer, 0x64, 0x95, 0xED, 0xFF);

				// Set the background color with the current RenderDrawColor (!!Clear screen!!)
				SDL_RenderClear(gWindowRenderer);

				// Place all rendering on the screen
				SDL_RenderPresent(gWindowRenderer);
			}
		}
	}

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

	return success;
}

void Close()
{
	// Deallocate surface
	SDL_FreeSurface(gWindowSurface);

	// Destroy window + Renderer
	SDL_DestroyWindow(gWindow);
	gWindow = NULL;
	SDL_DestroyRenderer(gWindowRenderer);
	gWindowRenderer = NULL;

	// Quit SDL
	IMG_Quit();
	SDL_Quit();
}