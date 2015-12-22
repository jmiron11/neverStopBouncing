#include "SDL.h"
#include "Input.h"
#include "Timer.h"

#include "Characters/BouncyBall.h"
#include "Environment/Environment.h"
#include "Information/Status.h"

#include <SDL2/SDL.h>
#include <iostream>

const char * GAME_NAME = "BADGAME";
const char * BOUNCE_BITMAP_PATH = "../bitmaps/bounce.bmp";
const char * GROUND_BITMAP_PATH = "../bitmaps/ground.bmp";
const char * ENVIR_ONE_BACKGROUND_PATH = "../bitmaps/sylviaIsCool.bmp";
const int GROUND_HEIGHT = 60;
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;
const int BOUNCE_WIDTH = 20;
const int BOUNCE_HEIGHT = 20;
const int BOUNCE_START_X = SCREEN_WIDTH/2;
const int BOUNCE_START_Y = SCREEN_HEIGHT-GROUND_HEIGHT-BOUNCE_HEIGHT;
const int STATUS_BAR_WIDTH = 100;
const int STATUS_BAR_HEIGHT = 40;
const int STATUS_BAR_X = SCREEN_WIDTH - STATUS_BAR_WIDTH;
const int STATUS_BAR_Y = 0;

bool g_running = true;

Input *g_input;
SDL *g_sdl;
Timer * g_timer;
Environment * g_environment;
Status * g_statusbar;
BouncyBall * maBoiBounce;
int curr_envir = 1;

void initGame();
void createBounce();
void eventLoop();
void cleanupGame();
void handleKeyboard();
void rerender();
void gameOverScreen();

void initEnvironmentOne();

int main(int argc, char *argv[])
{
	initGame();
	eventLoop();
	cleanupGame();
  return 0;
}

void initGame()
{
	g_sdl = new SDL(SCREEN_WIDTH, SCREEN_HEIGHT, GAME_NAME);
	g_input = new Input();
	g_timer = new Timer();
	g_environment = new Environment(g_sdl, SCREEN_WIDTH, SCREEN_HEIGHT);
	g_statusbar = new Status(g_sdl, STATUS_BAR_X, STATUS_BAR_Y, STATUS_BAR_WIDTH, STATUS_BAR_HEIGHT );

	createBounce();
	initEnvironmentOne();
}

void initEnvironmentOne()
{
	const int levelOneWidth = 2000;
	const int levelOneHeight = SCREEN_HEIGHT;
	const int bounceStartX = SCREEN_WIDTH/2;
	const int bounceStartY = 400 - BOUNCE_HEIGHT;
	g_environment->removeAllPlatforms();
	g_environment->removeAllTextboxes();
	g_environment->setBackground( ENVIR_ONE_BACKGROUND_PATH );
	g_environment->setDimension(levelOneWidth, levelOneHeight);
	g_environment->addPlatform( 0, 400, 500, SCREEN_HEIGHT-400, GROUND_BITMAP_PATH ); // floor level

	/* Pre pillars */
	g_environment->addPlatform( 460, 260, 80, 10, GROUND_BITMAP_PATH, true, 0, 40, 0, 50);
	g_environment->addPlatform( 550, 180, 80, 10, GROUND_BITMAP_PATH , true, 70, 0, 50, 0);

	g_environment->addPlatform( 750, 180, 80, 20, GROUND_BITMAP_PATH );

	/* Dem pillars */
	g_environment->addPlatform( 900, 180, 15, SCREEN_HEIGHT-180, GROUND_BITMAP_PATH );
	g_environment->addPlatform( 1000, 180, 15, SCREEN_HEIGHT-180, GROUND_BITMAP_PATH );
	g_environment->addPlatform( 1100, 180, 15, SCREEN_HEIGHT-180, GROUND_BITMAP_PATH );

	g_environment->addPlatform( 1700, 350, 200, 10, GROUND_BITMAP_PATH );
	g_environment->addPlatform( 1400, 250, 80, 80, GROUND_BITMAP_PATH );
	g_environment->addPlatform( 1800, 250, 100, 50, GROUND_BITMAP_PATH );

	g_environment->addTextbox("This is my house", 250, 250, 200, 60);
	g_environment->addTextbox("It is a very nice house", 650, 100, 270, 60);

	g_environment->setView(bounceStartX, SCREEN_HEIGHT/2);

	maBoiBounce->setStartLocation(bounceStartX, bounceStartY);
	maBoiBounce->reset();
}

void initEnvironmentTwo()
{
	const int levelTwoWidth = 2000;
	const int levelTwoHeight = SCREEN_HEIGHT;
	const int bounceStartX = SCREEN_WIDTH/2;
	const int bounceStartY = 400 - BOUNCE_HEIGHT;
	g_environment->removeAllPlatforms();
	g_environment->removeAllTextboxes();
	g_environment->setBackground( ENVIR_ONE_BACKGROUND_PATH );
	g_environment->setDimension(levelTwoWidth, levelTwoHeight);
	g_environment->addPlatform( 0, 400, 500, SCREEN_HEIGHT-400, GROUND_BITMAP_PATH ); // floor level

	/* Pre pillars */
	g_environment->addPlatform( 460, 260, 80, 10, GROUND_BITMAP_PATH, true, 0, 40, 0, 50);
	g_environment->addPlatform( 550, 180, 80, 10, GROUND_BITMAP_PATH , true, 70, 0, 50, 0);

	g_environment->addPlatform( 750, 180, 80, 20, GROUND_BITMAP_PATH );

	/* Dem pillars */
	g_environment->addPlatform( 900, 180, 15, SCREEN_HEIGHT-180, GROUND_BITMAP_PATH );
	g_environment->addPlatform( 1000, 180, 15, SCREEN_HEIGHT-180, GROUND_BITMAP_PATH );
	g_environment->addPlatform( 1100, 180, 15, SCREEN_HEIGHT-180, GROUND_BITMAP_PATH );

	g_environment->addPlatform( 1700, 350, 200, 10, GROUND_BITMAP_PATH );
	g_environment->addPlatform( 1400, 250, 80, 80, GROUND_BITMAP_PATH );
	g_environment->addPlatform( 1800, 250, 100, 50, GROUND_BITMAP_PATH );

	g_environment->addTextbox("This is not my house", 250, 250, 200, 60);
	g_environment->addTextbox("It is not a very nice house", 650, 100, 270, 60);

	g_environment->setView(bounceStartX, SCREEN_HEIGHT/2);

	maBoiBounce->setStartLocation(bounceStartX, bounceStartY);
	maBoiBounce->reset();
}

void createBounce()
{
	maBoiBounce = new BouncyBall( g_sdl, g_environment, BOUNCE_START_X, BOUNCE_START_Y, BOUNCE_WIDTH, BOUNCE_HEIGHT, BOUNCE_BITMAP_PATH );
}

void cleanupGame()
{
	delete g_sdl;
	delete g_input;
}


void eventLoop()
{
	int i = 0;
	while(g_running)
	{
		g_input->getInput();

		handleKeyboard();

		if(g_input->quitPressed())
		{
			g_running = false;
		}

		// Get the change in time since previous iteration
		float deltaTime = g_timer->timeSinceLastCall();
		maBoiBounce->update(deltaTime);
		g_environment->update(deltaTime);
		g_environment->setView(maBoiBounce->centerX(), maBoiBounce->centerY());

		// If the ball died, be super sad :'( 
		if(!maBoiBounce->isAlive())
		{
			gameOverScreen();
		}

		if(maBoiBounce->canLeaveArea())
		{
			initEnvironmentTwo();
		}

		// make some things appear on the screen cool cool cool.
		rerender();

		SDL_Delay(1);
	}
}

void rerender()
{
		g_sdl->renderBlank();

		g_environment->render();
		g_statusbar->render();
		maBoiBounce->render();

		g_sdl->presentRender();
}

void handleKeyboard()
{
	bool * keysPressed = g_input->getKeysPressed();

	//LALT + Q -> bye game :(
	if(keysPressed[SDL_SCANCODE_Q] && keysPressed[SDL_SCANCODE_LALT])
		g_running = false;

	//LALT+R -> restart level
	if(keysPressed[SDL_SCANCODE_R] && keysPressed[SDL_SCANCODE_LALT])
		initEnvironmentOne();

	if(keysPressed[SDL_SCANCODE_SPACE])
	{
		maBoiBounce->jump();
	}

	if(keysPressed[SDL_SCANCODE_LEFT] && !keysPressed[SDL_SCANCODE_RIGHT])
	{
		maBoiBounce->moveLeft();
	}
	else if (!keysPressed[SDL_SCANCODE_LEFT] && keysPressed[SDL_SCANCODE_RIGHT])
	{
		maBoiBounce->moveRight();
	}
	else
		maBoiBounce->stopMoving();
}

void gameOverScreen()
{
	g_statusbar->died();
	initEnvironmentOne();
}