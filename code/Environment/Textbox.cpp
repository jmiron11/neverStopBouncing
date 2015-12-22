#include "Textbox.h"

const int PADDING = 2;
const char * textFontPath = "../fonts/LiberationSans-Regular.ttf";


Textbox::Textbox( SDL* sdl, std::string text, const char * backBitmapFile, int x, int y, int width, int height)
	: m_sdl(sdl), m_text(text), m_x(x), m_y(y), m_width(width), m_height(height)
{
	m_backTexture = m_sdl->loadTexture(backBitmapFile);
}

Textbox::~Textbox()
{
	m_sdl->closeTexture(m_backTexture);
}

void Textbox::render(int c_x, int c_y)
{
	//Render the background of the text area
	m_sdl->renderRect(m_backTexture, m_x - c_x, m_y - c_y, m_width, m_height);

	//Render the texture for data
	SDL_Color black = { 0x00, 0x00, 0x00, 0x00 };
	SDL_Texture* fontTexture = m_sdl->loadFontTexture(m_text.c_str() , textFontPath, black, 30);
	m_sdl->renderRect(fontTexture, m_x+PADDING - c_x, m_y+PADDING - c_y, m_width - 2*PADDING, m_height/2-1);
	m_sdl->closeTexture(fontTexture);
}