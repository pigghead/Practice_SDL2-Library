#include <iostream>
#include <SDL.h>
#include <SDL_image.h>

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

				// Clear screen
				SDL_SetRenderDrawColor(gWindowRenderer, 0x64, 0x95, 0xED, 0xFF);
				SDL_RenderClear(gWindowRenderer);

				// Draw red quad
				SDL_Rect redQuad = { SCREEN_WIDTH / 4, SCREEN_HEIGHT / 4, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 };
				SDL_SetRenderDrawColor(gWindowRenderer, 0xFF, 0x00, 0x00, 0xFF);
				SDL_RenderFillRect(gWindowRenderer, &redQuad);

				// Draw green (empty) quad
				SDL_Rect greenQuad = { SCREEN_WIDTH / 6, SCREEN_HEIGHT / 6, SCREEN_WIDTH * 2 / 3, SCREEN_HEIGHT * 2 / 3 };
				SDL_SetRenderDrawColor(gWindowRenderer, 0x00, 0xFF, 0x00, 0xFF);
				SDL_RenderDrawRect(gWindowRenderer, &greenQuad);

				// Draw blue line
				SDL_SetRenderDrawColor(gWindowRenderer, 0x00, 0x00, 0xFF, 0xFF);
				SDL_RenderDrawLine(gWindowRenderer, 0, SCREEN_HEIGHT / 2, SCREEN_WIDTH, SCREEN_HEIGHT / 2);

				// Draw yellow line
				SDL_SetRenderDrawColor(gWindowRenderer, 0xFF, 0xFF, 0x00, 0xFF);

				for (size_t i = 0; i < SCREEN_HEIGHT; i+=4)
				{
					SDL_RenderDrawPoint(gWindowRenderer, SCREEN_WIDTH / 2, i);
				}

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

	return success;
}

void Close()
{
	// Deallocate surface
	SDL_FreeSurface(gWindowSurface);

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