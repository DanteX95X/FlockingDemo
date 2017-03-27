#ifndef STATE_H
#define STATE_H

#include <SDL2/SDL.h>

class State
{
public:
	virtual ~State() {};
	virtual void Update() {};
	virtual void HandleEvents(SDL_Event&) {};
	virtual void Render(SDL_Renderer* ) {};
};

#endif //STATE_H