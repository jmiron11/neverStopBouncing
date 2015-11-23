#include "Character.h"


#include <SDL2/SDL.h>
#include "../SDL.h"

Character::Character(SDL* sdl, Environment* envir, int x, int y, int width, 
					 int height, const char * bitMapFileName): m_sdl(sdl), m_envir(envir), 
																										 m_velX(0), m_velY(0),
					 										   										 m_x(x), m_y(y), 
											    			   									 m_width(width), 
											    			   									 m_height(height)
{
	m_texture = m_sdl->loadTexture(bitMapFileName);
}

Character::~Character()
{
	m_sdl->closeTexture(m_texture);
}

void Character::render()
{
	m_sdl->renderRect( m_texture, m_x - m_envir->viewX(), m_y - m_envir->viewY(), m_width, m_height );
}