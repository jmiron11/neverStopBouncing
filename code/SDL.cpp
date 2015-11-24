#include "SDL.h"

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#include <iostream>
#include <string>

const int BACKGROUND_RED = 0;
const int BACKGROUND_GREEN = 0;
const int BACKGROUND_BLUE = 0;
const int AUTODETECT = -1;

SDL::SDL(int windowWidth, int windowHeight, const char * title)
{
	// Initialize SDL
	if( SDL_Init( SDL_INIT_VIDEO ) != 0 )
	{
		std::cerr << "SDL Failed to initialize, SDL_ERROR: " << SDL_GetError() << std::endl;
		// Handle further
		return;
	}

	if( TTF_Init() != 0 )
	{
		std::cerr << "SDL Failed to initialize TTF " << std::endl;
		SDL_Quit();
		return;
	}

	// Create the main game window
	if((m_Window = SDL_CreateWindow( "First Window", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED
		, windowWidth, windowHeight, SDL_WINDOW_SHOWN )) == NULL)
	{
		std::cerr << "SDL Failed to create window, SDL_ERROR: " << SDL_GetError() << std::endl;
		SDL_Quit();
		// Handle further
		return;
	}

	// Create the main game renderer
	if((m_Renderer = SDL_CreateRenderer( m_Window, AUTODETECT, 0 )) == NULL)
	{
		std::cerr << "SDL Failed to create renderer, SDL_ERROR: " << SDL_GetError() << std::endl;
		SDL_Quit();
		//Handle further
		return;
	}

	// Set the renderer's color to black and load the default background
	SDL_SetRenderDrawColor( m_Renderer, 0x00, 0x00, 0x00, 0x00 );

	m_WindowWidth = windowWidth;
	m_WindowHeight = windowHeight;
}

SDL::~SDL()
{
	SDL_DestroyWindow( m_Window );
	m_Window = NULL;

	SDL_Quit();
}

void SDL::renderBlank()
{
	SDL_SetRenderDrawColor( m_Renderer, 0x00, 0x00, 0x00, 0x00 );
	SDL_RenderClear( m_Renderer );
}

void SDL::presentRender()
{
	SDL_RenderPresent( m_Renderer );
}

void SDL::renderRect(SDL_Texture * texture, int x, int y, int width, int height)
{
	SDL_Rect newRect = {x, y, width, height};
	SDL_RenderCopy(m_Renderer, texture, NULL, &newRect);
}

SDL_Texture* SDL::loadTexture( const char * bitMapFileName )
{
	SDL_Texture * newTexture = NULL;

	SDL_Surface * loadedSurface = loadBitmap(bitMapFileName);

	if((newTexture = SDL_CreateTextureFromSurface(m_Renderer, loadedSurface)) == NULL)
	{
		std::cerr << "SDL Failed to create texture from surface, SDL_ERROR: " << SDL_GetError() << std::endl;
		return NULL;
	}
	closeBitmap(loadedSurface);

	return newTexture;
}

SDL_Texture* SDL::loadFontTexture( std::string text, const char * fontFile, SDL_Color color, int fontSize)
{
	TTF_Font* font = NULL;
	SDL_Surface* fontSurface = NULL;
	SDL_Texture* fontTexture = NULL;

	if((font = TTF_OpenFont(fontFile, fontSize)) == NULL)
	{
		std::cerr << "Failed to open font" << std::endl;
		return NULL;
	}

	if((fontSurface = TTF_RenderText_Blended(font, text.c_str(), color)) == NULL)
	{
		std::cerr << "Failed to get surface from font" << std::endl;
		return NULL;
	}

	if((fontTexture = SDL_CreateTextureFromSurface(m_Renderer, fontSurface)) == NULL)
	{
		std::cerr << "Failed to get texture from surface" << std::endl;
		return NULL;
	}

	SDL_FreeSurface(fontSurface);
	TTF_CloseFont(font);
	return fontTexture;
}

void SDL::closeTexture(SDL_Texture * texture)
{
	SDL_DestroyTexture(texture);
}

SDL_Surface *SDL::loadBitmap(const char * bitMapFileName)
{
	SDL_Surface * loadedBMP = NULL;
	if((loadedBMP  = SDL_LoadBMP(bitMapFileName)) == NULL)
	{
		std::cerr << "SDL Failed to load BMP, SDL_Error: " << SDL_GetError() << std::endl;
		return NULL;
	}
	return loadedBMP;
}

void SDL::closeBitmap(SDL_Surface * bitMap)
{
	SDL_FreeSurface(bitMap);
}

int SDL::getWindowWidth()
{
	return m_WindowWidth;
}

int SDL::getWindowHeight()
{
	return m_WindowHeight;
}