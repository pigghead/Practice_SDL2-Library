#pragma once
#include <SDL.h>
class LButton
{
public:
	// Initialize internal variables
	LButton();

	// Destructor
	~LButton();

	// Set top left position of the button
	void setPosition(int x, int y);

	// Handle mouse events
	void handleEvent(SDL_Event* e);

	// Shows the button's sprite
	void render();

	// free space
	void free();
private:
	// Position of the button
	SDL_Point mPosition;

	// Enum for the various button states
	static enum LButtonSprite
	{
		BUTTON_SPRITE_MOUSE_OUT = 0,
		BUTTON_SPRITE_MOUSE_OVER_MOTION = 1,
		BUTTON_SPRITE_MOUSE_DOWN = 2,
		BUTTON_SPRITE_MOUSE_UP = 3,
		BUTTON_SPRITE_MOUSE_TOTAL = 4
	};

	// Button dimensions
	int bWidth;
	int bHeight;

	// The button's sprite
	LButtonSprite mCurrentSprite;

	// Sprite sheet accepted by button

};

