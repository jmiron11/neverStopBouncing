#include "Platform.h"
#include "../SDL.h"

#include <iostream>

const int PLATFORM_FUN_CONSTANT = 1;

Platform::Platform(SDL* sdl, int x, int y, int width, int height, const char * bitmapFileName, 
									 bool animated, int xRange, int yRange, int xVel, int yVel)
	: m_sdl(sdl), m_x(x), m_y(y), 
		m_width(width), m_height(height), m_animated(animated), 
		m_xVel(xVel), m_yVel(yVel)
{
	m_texture = m_sdl->loadTexture(bitmapFileName);
	m_startX = x;
	m_endX = x+xRange;
	m_startY = y;
	m_endY = y+yRange;
}

Platform::~Platform()
{
	m_sdl->closeTexture(m_texture);
}

void Platform::update(float deltaTime)
{
	if(m_animated)
	{
		if(m_x > m_endX || m_x < m_startX)
		{
			m_xVel = -m_xVel;
		}

		if(m_y > m_endY || m_y < m_startY)
		{
			m_yVel = -m_yVel;
		}

		m_x += m_xVel * deltaTime * PLATFORM_FUN_CONSTANT;
		m_y += m_yVel * deltaTime * PLATFORM_FUN_CONSTANT;
	}
}