#include <iostream>
#include "window/window.h"
#include "objects/prop.h"
#include "utilities/timer.h"
#include "objects/actor.h"
#include <queue>

int main(int argc, char** argv)
{
	bool isDone = false;

	SDL_Event event;
	Window window;

	while( !isDone )
	{
		while(SDL_PollEvent(&event))
		{
			if(event.type == SDL_QUIT)
			{
				isDone = true;
			}
		}

		Timer::Instance().Update();

		SDL_RenderClear(window.GetRenderer());

		SDL_RenderPresent(window.GetRenderer());
	}

	return 0;
}
