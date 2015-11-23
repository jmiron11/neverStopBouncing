#ifndef CHARACTER_H_
#define CHARACTER_H_

#include <SDL2/SDL.h>
#include "../SDL.h"
#include "../Environment/Environment.h"

class Character{
 public:
 	Character(SDL* sdl, Environment* envir, int x, int y, int width, int height, const char* bitMapFileName);
 	~Character();

 	// draw the character to the renderer
 	void render();

 	// function to update position and velocities
 	virtual void update(float deltaTime) = 0;

 	// representation of the characters position and movement
 	float m_velX;
 	float m_velY;
 	float m_x;
 	float m_y;

 	// size of the character
 	int m_width;
 	int m_height;

 	// SDL related textures and wrappers
 	Environment * m_envir;
 	SDL* m_sdl;
 	SDL_Texture* m_texture;
};

#endif