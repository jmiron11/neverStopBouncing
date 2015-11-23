#ifndef STATUS_H_
#define STATUS_H_

#include "../SDL.h"

class Status{
public:
	Status(SDL* sdl);
	~Status();
	void render();
private:
	SDL* m_sdl;

};

#endif