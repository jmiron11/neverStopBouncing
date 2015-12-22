#include "BouncyBall.h"

#include <iostream>
#include <cmath>

const int platform = 420;
const float GRAVITY_CONSTANT = 9.81*10;
const float FUN_CONSTANT = 5;
const float SLIDE_CONSTANT = 1.02;
const float X_CONSTANT = 80;
const float MAX_CHARGE = 1000;
const float SMALL_ENOUGH_NUMBER = 0.01;
bool jumping = false;
bool sliding = true;
bool canSlide = false;

BouncyBall::BouncyBall(SDL* sdl, Environment* envir, int x, int y, int width, int height, const char* bitMapFileName)
	:Character(sdl, envir, x, y, width, height, bitMapFileName), alive(true), jumping(false), sliding(false), canSlide(false), canLeave(false) { }

BouncyBall::~BouncyBall()
{
}

void BouncyBall::jump()
{
	if(!jumping){
		canSlide = true;
		sliding = false;
		jumping = true;
		m_velY = -170;
	}
}

void BouncyBall::update(float deltaTime)
{
	// If we are jumping, velocity is affected by gravity */
	if(jumping)
		m_velY = m_velY + GRAVITY_CONSTANT * deltaTime * FUN_CONSTANT;

	// set new X and Y values and check boundaries
	m_y += m_velY * deltaTime * FUN_CONSTANT;
	m_x += m_velX * deltaTime * FUN_CONSTANT;

	CollisionType col;
	Platform * hitPlatform = NULL;
	if((col = platformCollision(hitPlatform)) != NONE)
	{
		handleCollision(col, hitPlatform);
	}

	if(sliding)
	{
		m_velX /= SLIDE_CONSTANT;

		if(abs(m_velX) <= SMALL_ENOUGH_NUMBER){
			m_velX = 0;
			sliding = false;
			canSlide = true;
		}
	}
}

CollisionType BouncyBall::platformCollision(Platform *& hitPlatform)
{
	if(m_x + m_width >= m_envir->levelWidth())
		return BORDER_RIGHT;
	if(m_x <= 0)
		return BORDER_LEFT;
	if(m_y < 0)
		return BORDER_UP;
	if(m_y + m_height >= m_envir->levelHeight())
		return OFFSCREEN;


	for(int i = 0; i < m_envir->platforms.size(); ++i)
	{
		// if bottom of ball hits top of platform
		Platform* cur = m_envir->platforms[i];
		if((m_y + m_height >= cur->m_y) && 
			 (m_y < cur->m_y) && 
			 (m_x + m_width > cur->m_x) &&
			 (m_x < cur->m_x + cur->m_width))
		{
			hitPlatform = m_envir->platforms[i];
			return PLATFORM_DOWN;
		}

		// if top of ball hits bottom of platform
		if((m_y <= cur->m_y + cur->m_height) && 
			 (m_y + m_height > cur->m_y + cur->m_height) && 
			 (m_x + m_width > cur->m_x) &&
			 (m_x < cur->m_x + cur->m_width))
		{
			hitPlatform = m_envir->platforms[i];
			return PLATFORM_UP;
		}

		// if left of ball hits left of platform
		if((m_y + m_height > cur->m_y) && 
			 (m_y < cur->m_y + cur->m_height) && 
			 (m_x <= cur->m_x + cur->m_width) &&
			 (m_x + m_width > cur->m_x + cur->m_width))
		{
			hitPlatform = m_envir->platforms[i];
			return PLATFORM_LEFT;
		}

		// if right of ball hits left of platform
		if((m_y + m_height > cur->m_y) && 
			 (m_y < cur->m_y + cur->m_height) && 
			 (m_x + m_width >= cur->m_x) &&
			 (m_x < cur->m_x))
		{
			hitPlatform = m_envir->platforms[i];
			return PLATFORM_RIGHT;
		}
	}

	return NONE;
}

void BouncyBall::handleCollision(CollisionType c, Platform * hitPlatform)
{
	switch(c)
	{
		case BORDER_LEFT:
			m_velX = -m_velX; //Bounce off border and keep x within range
			m_x = 0;
			break;

		case BORDER_RIGHT:
			// m_velX = -m_velX; //Bounce off border and keep x within range
			// m_x = m_envir->levelWidth() - m_width;
			canLeave = true;
			break;

		case BORDER_UP:
			break;

		case BORDER_DOWN:
			// m_y =  m_envir->levelHeight() - m_height;
			// jumping = false;

			// //if it can slide, let it start sliding
			// if(canSlide){ 
			// 	sliding = true; 
			// 	canSlide = false; 
			// }

			break;

		case PLATFORM_LEFT:
			m_velX = -m_velX;
			m_x = hitPlatform->m_x + hitPlatform->m_width;
			break;

		case PLATFORM_RIGHT:
			m_velX = -m_velX;
			m_x = hitPlatform->m_x - m_width;
			break;

		case PLATFORM_UP:
			m_velY = -m_velY;
			m_y = hitPlatform->m_y + hitPlatform->m_height;
			break;

		case PLATFORM_DOWN:
			m_y = hitPlatform->m_y - m_height;
			jumping = false;

			if(canSlide)
			{
				sliding = true;
				canSlide = false;
			}
			break;

		case OFFSCREEN:
			alive = false;
			break;
	}
}

bool BouncyBall::jumpEnded()
{
	return jumping;
}

void BouncyBall::moveLeft()
{
	if(jumping && !sliding)
	{
		m_velX = -80;
	}
	else if (!sliding)
	{
		m_velX = -20;
	}
}

void BouncyBall::moveRight()
{
	if(jumping && !sliding)
	{
		m_velX = 80;
	}
	else if (!sliding)
	{
		m_velX = 20;
	}
}

void BouncyBall::stopMoving()
{
	// if(m_velX != 0)
	// 	m_velX /= SLIDE_CONSTANT;
}

int BouncyBall::centerX()
{
	return m_x + m_width/2;
}

int BouncyBall::centerY()
{
	return m_y + m_height/2;
}

void BouncyBall::setStartLocation(int x, int y)
{
	m_x = x;
	m_y = y;
}

bool BouncyBall::isAlive()
{
	return alive;
}

void BouncyBall::reset()
{
	alive = true;
	canLeave = false;
	m_velX = 0;
	m_velY = 0;
}

bool BouncyBall::canLeaveArea()
{
	return canLeave;
}