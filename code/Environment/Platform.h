#ifndef PLATFORM_H_
#define PLATFORM_H_

#include "../SDL.h"

#include <SDL2/SDL.h>

class Platform{
 public:
 	Platform(SDL* sdl, int x, int y, int width, int height, const char * bitmapFileName, bool animated, int xRange, int yRange, int xVel, int yVel);
 	~Platform();

 	void update(float deltaTime);

 	float m_x;
 	float m_y;
 	int m_width;
 	int m_height;
 	bool m_animated;
 	int m_startX;
 	int m_endX;
 	int m_startY;
 	int m_endY;
 	float m_xVel;
 	float m_yVel;

 	SDL_Texture * m_texture;


 private:
 	SDL* m_sdl;
};


#endif