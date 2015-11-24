#include "Status.h"

#include "../SDL.h"

#include <string>

const char * backgroundFilePath = "../bitmaps/status.bmp";
const char * fontPath = "../fonts/LiberationSans-Regular.ttf";
const int PADDING = 2;

Status::Status(SDL* sdl, int x, int y, int width, int height): m_sdl(sdl), m_x(x), m_y(y), m_width(width), m_height(height), numDeaths(0){
	m_backTexture = m_sdl->loadTexture(backgroundFilePath);
}

Status::~Status(){
	m_sdl->closeTexture(m_backTexture);
}

void Status::render()
{
	m_sdl->renderRect(m_backTexture, m_x, m_y, m_width, m_height);

	SDL_Color white = { 0xFF, 0xFF, 0xFF, 0xFF };
	SDL_Texture* fontTexture = m_sdl->loadFontTexture("Deaths: " + std::to_string(numDeaths) , fontPath, white, 30);
	m_sdl->renderRect(fontTexture, m_x+PADDING, m_y+PADDING, m_width - 2*PADDING, m_height/2-1);
}

void Status::died()
{
	numDeaths++;
}