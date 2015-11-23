#ifndef SDL_H_
#define SDL_H_

#include <SDL2/SDL.h>

class SDL
{
public:

	// Initialization of SDL, m_Window, and m_Screen
	SDL(int windowWidth, int windowHeight, const char * title);

	// Destructor of SDL, m_Window (m_Screen cleaned up by m_Window)
	~SDL();

	void renderBlank();
	void presentRender();

	// Functions to handle loading Textures
	SDL_Texture* loadTexture( const char* bitMapFileName );	
	void closeTexture(SDL_Texture * texture);

	// Functions to handle loading BMPs
	SDL_Surface * loadBitmap(const char * bitMapFileName);
	void closeBitmap(SDL_Surface * bitmap);

	void renderRect(SDL_Texture * texture, int x, int y, int width, int height);

	int getWindowWidth();
	int getWindowHeight();

private:
	SDL_Window * m_Window;
	SDL_Surface * m_Screen;
	SDL_Renderer * m_Renderer;

	int m_WindowWidth;
	int m_WindowHeight;
};


#endif