#ifndef BOUNCYBALL_H_
#define BOUNCYBALL_H_

#include "Character.h"

enum CollisionType{
	NONE,
	BORDER_LEFT,
	BORDER_RIGHT,
	BORDER_UP,
	BORDER_DOWN,
	PLATFORM_LEFT,
	PLATFORM_RIGHT,
	PLATFORM_UP,
	PLATFORM_DOWN,
	OFFSCREEN
};


class BouncyBall: public Character{
public: 
	BouncyBall(SDL* sdl, Environment* envir, int x, int y, int width, int height, const char* bitMapFileName);
	~BouncyBall();

	// change y velocity to act as if jumping
	void jump();

	// update x, y, and velocity values
	void update(float deltaTime);

	// function sto modify velocity
	int setXVelocity(int value);
	int setYVelocity(int value);

	void setStartLocation(int x, int y);

	// whether or not the ball is currently jumping
	bool jumpEnded();

	bool isAlive();
	void reset();

	// handle movement of the ball
	void moveLeft();
	void moveRight();
	void stopMoving();

	int centerX();
	int centerY();

private:
	CollisionType platformCollision(Platform *& hitPlatform);
	void handleCollision(CollisionType c, Platform * hitPlatform);
	CollisionType multiCollision();

	bool alive;
	bool jumping;
	bool sliding;
	bool canSlide;
};


#endif