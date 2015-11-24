#ifndef ENVIRONMENT_H_
#define ENVIRONMENT_H_

#include <vector>
#include <SDL2/SDL.h>

#include "../SDL.h"
#include "Platform.h"

class Environment
{
public:
	Environment(SDL* sdl, int viewWidth, int viewHeight);
	~Environment();

	void render();

	void removeAllPlatforms();
	void addPlatform(int x, int y, int width, int height, const char* bitmapFileName, 
									 bool animated = false, int xRange = 0, int yRange = 0, int xVel = 0, int yVel = 0);


	void update(float deltaTime);

	void setDimension(int width, int height);
	void setView(int x, int y);
	void setBackground(const char * bitmapFileName);

	/* Helper functions to get member values SHOULD SET TO CONST*/
	int viewX();
	int viewY();
	int levelWidth();
	int levelHeight();

	std::vector<Platform*> platforms;

private:
	
	class View{
	public:
		int m_x;
		int m_y;
		int m_width;
		int m_height;
	};


	SDL* m_sdl;
	SDL_Texture* m_background;
	int m_width;
	int m_height;
	View m_camera; 

	void clear();
};	

#endif