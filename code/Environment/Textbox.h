#ifndef TEXTBOX_H_
#define TEXTBOX_H_

#include "../SDL.h"

#include <string>
#include <SDL2/SDL.h>

class Textbox
{
public:
	Textbox( SDL* sdl, std::string text, const char * backBitmapFile, int x, int y, int width, int height);
	~Textbox();

	void render(int c_x, int c_y);


private:
	SDL* m_sdl;
	SDL_Texture* m_backTexture;
	std::string m_text;

	int m_x;
	int m_y;
	int m_width;
	int m_height;

};

#endif