#include "Environment.h"

#include "Textbox.h"

#include <iostream>
#include <SDL2/SDL.h>
#include <cstdint>

Environment::Environment(SDL* sdl, int viewWidth, int viewHeight): m_sdl(sdl)
{
	m_camera.m_x = 0;
	m_camera.m_y = 0;
	m_background = NULL;

	m_camera.m_width = viewWidth;
	m_camera.m_height = viewHeight;
}


Environment::~Environment()
{
	clear();
}

void Environment::render()
{
	// render background
	if(m_background != NULL){
		m_sdl->renderSection( m_background, m_camera.m_x, m_camera.m_y, m_camera.m_width, m_camera.m_height, 0, 0, m_camera.m_width, m_camera.m_height );
	}

	for(int i = 0; i < platforms.size(); ++i)
	{
		/* render each rectangle if it is within the area */
		m_sdl->renderRect( platforms[i]->m_texture, 
											 platforms[i]->m_x - m_camera.m_x, 
											 platforms[i]->m_y - m_camera.m_y, 
											 platforms[i]->m_width, 
											 platforms[i]->m_height );
	}

	for(int i = 0; i < textboxes.size(); ++i)
	{
		/* render each rectangle if it is within the area */
		textboxes[i]->render(m_camera.m_x, m_camera.m_y);
	}
}	

void Environment::addPlatform(int x, int y, int width, int height, const char* bitmapFileName, 
													    bool animated, int xRange, int yRange, int xVel, int yVel)
{
	/* Check that it doesn't conflict with any existing platforms */


	/* Add platform to platform LL */
	Platform* newPlat = new Platform(m_sdl, x, y, width, height, bitmapFileName, animated, xRange, yRange, xVel, yVel);
	platforms.push_back(newPlat);
}

void Environment::removeAllPlatforms()
{
	for(int i = 0; i < platforms.size(); ++i)
	{
		delete platforms[i];
		platforms[i] = NULL;
	}

	platforms.clear();
}

void Environment::clear()
{
	removeAllPlatforms();
	removeAllTextboxes();

	if(m_background != NULL)
		m_sdl->closeTexture(m_background);
}

void Environment::setDimension(int width, int height)
{
	m_width = width;
	m_height = height;
}

void Environment::setView(int x, int y)
{
	m_camera.m_x = (x - m_sdl->getWindowWidth()/2);
	m_camera.m_y = (y - m_sdl->getWindowHeight()/2);

	if(m_camera.m_x < 0) m_camera.m_x = 0;
	if(m_camera.m_y < 0) m_camera.m_y = 0;
	if(m_camera.m_x > m_width - m_sdl->getWindowWidth()) m_camera.m_x = m_width - m_sdl->getWindowWidth();
	if(m_camera.m_y > m_height - m_sdl->getWindowHeight()) m_camera.m_y = m_height - m_sdl->getWindowHeight();
}

int Environment::viewX()
{
	return m_camera.m_x;
}


int Environment::viewY()
{
	return m_camera.m_y;
}

int Environment::levelWidth()
{
	return m_width;
}

int Environment::levelHeight()
{
	return m_height;
}

void Environment::update(float deltaTime)
{
	for(int i = 0; i < platforms.size(); ++i)
		platforms[i]->update(deltaTime);
}

void Environment::setBackground(const char * bitmapFileName)
{
	m_background = m_sdl->loadTexture(bitmapFileName);
}

void Environment::removeAllTextboxes()
{
	for(int i = 0; i < textboxes.size(); ++i)
		delete textboxes[i];

	textboxes.clear();
}

void Environment::addTextbox( std::string text , int x, int y, int width, int height )
{
	Textbox* newTextbox = new Textbox(m_sdl, text, "../bitmaps/white.bmp", x, y, width, height);
	textboxes.push_back(newTextbox);
}