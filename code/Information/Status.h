#ifndef STATUS_H_
#define STATUS_H_

#include "../SDL.h"

class Status{
public:
	Status(SDL* sdl, int x, int y, int width, int height);
	~Status();
	void render();

	void died();
private:
	SDL* m_sdl;
	SDL_Texture* m_backTexture;

	int numDeaths;

	int m_x;
	int m_y;
	int m_width;
	int m_height;
};

#endif