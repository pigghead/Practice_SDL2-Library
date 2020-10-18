#include "LButton.h"
#include "LTexture.h"

LButton::LButton()
{
	mPosition.x = 0;
	mPosition.y = 0;

	mCurrentSprite = BUTTON_SPRITE_MOUSE_OUT;
};

void LButton::setPosition(int x, int y)
{
	mPosition.x = x;
	mPosition.y = y;
}

void LButton::handleEvent(SDL_Event* e)
{
	// If a mouse event is detected
	if (e->type == SDL_MOUSEMOTION || e->type == SDL_MOUSEBUTTONDOWN || e->type == SDL_MOUSEBUTTONUP)
	{
		// Get mouse position
		int x, y;
		SDL_GetMouseState(&x, &y);

		bool inside = true;
		// Left of the button
		if (x < mPosition.x)
		{
			inside = false;
		}
		// Right of the button
		else if (x > mPosition.x + bWidth)
		{
			inside = false;
		}
		// Above the button
		else if (y < mPosition.y)
		{
			inside = false;
		}
		else if (y > mPosition.y + bHeight)
		{
			inside = false;
		}

		if (!inside)
		{
			mCurrentSprite = BUTTON_SPRITE_MOUSE_OUT;
		}
		else
		{
			switch (e->type)
			{
				case SDL_MOUSEMOTION:
					mCurrentSprite = BUTTON_SPRITE_MOUSE_OVER_MOTION;
					break;
				case SDL_MOUSEBUTTONDOWN:	
					mCurrentSprite = BUTTON_SPRITE_MOUSE_DOWN;
					break;
				case SDL_MOUSEBUTTONUP:
					mCurrentSprite = BUTTON_SPRITE_MOUSE_UP;
					break;
				default:
					break;
			}
		}
	}
};

void LButton::render()
{
	// Show current button sprite
};

void LButton::free()
{
	if (tex != NULL)
	{
		SDL_DestroyTexture(tex);
		tex = NULL;
		bWidth = 0;
		bHeight = 0;
	}
};
