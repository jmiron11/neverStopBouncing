#include "Status.h"

#include "../SDL.h"

#include <string>

const char * statusFontPath = "../fonts/LiberationSans-Regular.ttf";
const char * statusBackgroundPath = "../bitmaps/status.bmp";
const int PADDING = 2;

Status::Status(SDL* sdl, int x, int y, int width, int height): m_sdl(sdl), m_x(x), m_y(y), m_width(width), m_height(height), numDeaths(0){
	m_backTexture = m_sdl->loadTexture(statusBackgroundPath);
}

Status::~Status(){
	m_sdl->closeTexture(m_backTexture);
}

void Status::render()
{
	//Render the background of the status area
	m_sdl->renderRect(m_backTexture, m_x, m_y, m_width, m_height);

	//Render the texture for reporting number of deaths
	SDL_Color white = { 0xFF, 0xFF, 0xFF, 0xFF };
	SDL_Texture* fontTexture = m_sdl->loadFontTexture("Deaths: " + std::to_string(numDeaths) , statusFontPath, white, 30);
	m_sdl->renderRect(fontTexture, m_x+PADDING, m_y+PADDING, m_width - 2*PADDING, m_height/2-1);
	m_sdl->closeTexture(fontTexture);
}

void Status::died()
{
	numDeaths++;
}