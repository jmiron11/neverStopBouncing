#include "Timer.h"


#include <SDL2/SDL.h>


Timer::Timer(): m_prevTime(0.0f)
{
	SDL_Init(SDL_INIT_TIMER);
}


Timer::~Timer(){ }

float Timer::timeSinceCreated()
{
	return SDL_GetTicks() / 1000.0f;
}

float Timer::timeSinceLastCall()
{
	float curTime = timeSinceCreated();
	float deltaTime = curTime - m_prevTime;
	m_prevTime = curTime;

	return deltaTime;
}