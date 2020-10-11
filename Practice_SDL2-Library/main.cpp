#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include "OptimizedSurfaceLoader.h"
#undef main  // This is necessary due to an unresolved main external when using SDL2

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
SDL_Window* win = NULL;					// Window we will render to
SDL_Surface* winSurface = NULL;			// The surface within the window
SDL_Surface* gHelloWorld = NULL;		// Image to be loaded + shown
SDL_Surface* gKeyPressSurfaces[KEY_PRESS_SURFACE_TOTAL];	// Array of our possible key presses
SDL_Surface* gCurrentSurface = NULL;	// Current displayed image

SDL_Renderer* gWindowRenderer = NULL;	// Renderer for the window


/* Function prototypes */
// Startup + window creation
bool Init();

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

			// Default 

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
					else if (e.type == SDL_KEYDOWN)
					{
						switch (e.key.keysym.sym)
						{
						case SDLK_UP:
							gCurrentSurface = gKeyPressSurfaces[KEY_PRESS_SURFACE_UP];
							break;
						case SDLK_DOWN:
							gCurrentSurface = gKeyPressSurfaces[KEY_PRESS_SURFACE_DOWN];
							break;
						case SDLK_LEFT:
							gCurrentSurface = gKeyPressSurfaces[KEY_PRESS_SURFACE_LEFT];
							break;
						case SDLK_RIGHT:
							gCurrentSurface = gKeyPressSurfaces[KEY_PRESS_SURFACE_RIGHT];
							break;
						default:
							break;
						}
					}
				}

				// Apply image
				SDL_BlitSurface(gCurrentSurface, NULL, winSurface, NULL);

				// Update surface 
				SDL_UpdateWindowSurface(win);
			}
		}
	}

	return 0;
}

bool Init()
{
	bool success = true;

	// Error catch on initialization
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		std::cout << "Initialization error: " << SDL_GetError() << std::endl;
		success = false;
	} 
	else
	{
		// Window Creation
		win = SDL_CreateWindow("My second window", 100, 100, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);

		// Error catch on window creation
		if (win == NULL)
		{
			std::cout << "Error creating window: " << SDL_GetError() << std::endl;
			success = false;
		}
		else
		{
			// Initialize SDL_Image with PNG loading
			int imgFlags = IMG_INIT_PNG;

			// Error check PNG loading enabled
			if (!(IMG_Init(imgFlags) & imgFlags))
			{
				std::cout << "Error initializing SDL_Image: " << IMG_GetError() << std::endl;
				success = false;
			}
			else
			{
				// Get window surface
				winSurface = SDL_GetWindowSurface(win);
			}
		}
	}

	return success;
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
		win = SDL_CreateWindow("Window with Renderer", 100, 100, SCREEN_WIDTH, SCREEN_HEIGHT, 0);

		// Error check
		if (win == NULL)
		{
			std::cout << "Error creating window: " << SDL_GetError() << std::endl;
			success = false;
		}
		else
		{
			// Create the renderer
			gWindowRenderer = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED);

			// Error check renderer
			if (gWindowRenderer == NULL)
			{
				std::cout << "Error creating renderer: " << SDL_GetError() << std::endl;
				success = false;
			}
			else
			{
				// Set render color
				SDL_SetRenderDrawColor(gWindowRenderer, 0XFF, 0XFF, 0XFF, 0XFF);

				// Initialize PNG loading
				int imgFlags = IMG_INIT_PNG;  // Value of 2

				if (!(IMG_Init(imgFlags) & imgFlags))
				{
					std::cout << "Error initializing IMG: " << IMG_GetError() << std::endl;
					success = false;
				}
				else
				{
					winSurface = SDL_GetWindowSurface(win);
				}
			}
		}
	}

	return success;
}

bool LoadMedia()
{
	// Success flag
	bool success = true;

	// Splash picture
	gHelloWorld = SDL_LoadBMP("media/Hello_world.bmp");

	// Error catch the image being loaded
	if (gHelloWorld == NULL)
	{
		std::cout << "Error loading image: " << SDL_GetError() << std::endl;
		success = false;
	}

	// Default key press
	gKeyPressSurfaces[KEY_PRESS_SURFACE_DEFAULT] = OptimizedSurfaceLoader::OptimizedLoadedSurface("media/default.bmp", winSurface);
	if (gKeyPressSurfaces[KEY_PRESS_SURFACE_DEFAULT] == NULL)
	{
		std::cout << "Error loading default image: " << SDL_GetError() << std::endl;
		success = false;
	}

	// Up key press
	gKeyPressSurfaces[KEY_PRESS_SURFACE_UP] = OptimizedSurfaceLoader::OptimizedLoadedSurface("media/up.bmp", winSurface);
	if (gKeyPressSurfaces[KEY_PRESS_SURFACE_UP] == NULL)
	{
		std::cout << "Error loading up image: " << SDL_GetError() << std::endl;
		success = false;
	}

	// Down key press
	gKeyPressSurfaces[KEY_PRESS_SURFACE_DOWN] = OptimizedSurfaceLoader::OptimizedLoadedSurface("media/down.bmp", winSurface);
	if (gKeyPressSurfaces[KEY_PRESS_SURFACE_DOWN] == NULL)
	{
		std::cout << "Error loading down image: " << SDL_GetError() << std::endl;
		success = false;
	}

	// Left key press
	gKeyPressSurfaces[KEY_PRESS_SURFACE_LEFT] = OptimizedSurfaceLoader::OptimizedLoadedSurface("media/left.bmp", winSurface);
	if (gKeyPressSurfaces[KEY_PRESS_SURFACE_LEFT] == NULL)
	{
		std::cout << "Error loading left image: " << SDL_GetError() << std::endl;
		success = false;
	}

	// Right key press
	gKeyPressSurfaces[KEY_PRESS_SURFACE_RIGHT] = OptimizedSurfaceLoader::OptimizedLoadedSurface("media/right.bmp", winSurface);
	if (gKeyPressSurfaces[KEY_PRESS_SURFACE_RIGHT] == NULL)
	{
		std::cout << "Error loading right image: " << SDL_GetError() << std::endl;
		success = false;
	}

	return success;
}

void Close()
{
	// Deallocate surface
	SDL_FreeSurface(winSurface);

	// Destroy window
	SDL_DestroyWindow(win);
	win = NULL;

	// Quit SDL
	SDL_Quit();
}