#include "Input.h"
#include <SDL2/SDL.h>


Input::Input()
{

	m_quitPressed = false;
	for(int i = 0; i < NUM_KEYS; ++i)
	{
		m_keysPressed[i] = false;
	}
}

Input::~Input()
{

}

void Input::getInput()
{
	SDL_Event event;
	if (SDL_PollEvent(&event))
	{
		switch(event.type)
		{
			case SDL_QUIT:
			{
				m_quitPressed = true;
				break;
			}
			case SDL_KEYDOWN:
			{
				m_keysPressed[event.key.keysym.scancode] = true;
				break;
			}
			case SDL_KEYUP:
			{
				m_keysPressed[event.key.keysym.scancode] = false;
				break;
			}

		}
	}
}

bool* Input::getKeysPressed()
{
	return m_keysPressed;
}

bool Input::quitPressed()
{
	return m_quitPressed;
}