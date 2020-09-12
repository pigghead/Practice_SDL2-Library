#include <iostream>
#include <SDL.h>
#undef main  // This is necessary due to an unresolved main external when using SDL2

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

// Our window and surfaces
SDL_Window* win = NULL;				// Window we will render to
SDL_Surface* winSurface = NULL;		// The surface within the window
SDL_Surface* gHelloWorld = NULL;	// Image to be loaded + shown

/* Function prototypes */
// Startup + window creation
bool Init();

// Loads all media
bool LoadMedia();

// Free media + shut down SDL
void Close();

int main(int argc, char* args[])
{
	// SDL_Init allows initialization of what is in ( )
	/*if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
	{
		std::cout << "Initialization error" << std::endl;
		//system("Pause");
		return 1;
	}*/

	// Startup/ Initialization
	if (!Init())
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
			// Apply image
			SDL_BlitSurface(gHelloWorld, NULL, winSurface, NULL);

			// Update surface 
			SDL_UpdateWindowSurface(win);

			// Wait two seconds
			SDL_Delay(2000);
		}
	}

	// Free resources + close SDL
	Close();

	/*
	// If video init returns -1, there is an error
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		std::cout << "Initialization error: " << SDL_GetError() << std::endl;
		return 1;
	}

	// Creating a window:
	// - an SDL_Window pointer obj is initialized with SDL_CreateWindow method
	win = SDL_CreateWindow("my 1st window", 100, 100, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);

	// Make sure win creation successful
	if (!win)
	{
		std::cout << "Error creating window" << std::endl;
		return 1;
	}

	// Create a surface
	winSurface = SDL_GetWindowSurface(win);

	// Make sure surface creation/ get was successful
	if (!winSurface)
	{
		std::cout << "Error getting window surface" << std::endl;
		return 1;
	}
	*/

	// drawing occurs here
	/*SDL_FillRect(winSurface, NULL, SDL_MapRGB(winSurface->format, 255, 90, 120));

	SDL_UpdateWindowSurface(win);*/
	/* END main game loop */

	//LoadMedia();

	//system("pause");

	// Destroy window + quit
	/*SDL_DestroyWindow(win);
	SDL_Quit();*/

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
			// Get window surface
			winSurface = SDL_GetWindowSurface(win);
		}
	}

	return success;
}

bool LoadMedia()
{
	// Success flag
	bool success = true;

	// Splash picture
	gHelloWorld = SDL_LoadBMP("Hello_world.bmp");

	// Error catch the image being loaded
	if (gHelloWorld == NULL)
	{
		std::cout << "Error loading image: " << SDL_GetError() << std::endl;
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