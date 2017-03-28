#include <iostream>
#include "window/window.h"
#include "objects/prop.h"
#include "utilities/timer.h"
#include "objects/agent.h"
#include <queue>
#include "objects/flocker_state.h"
#include <stdlib.h>
#include <time.h>

int main(int argc, char** argv)
{
	srand(time(nullptr));
	
	bool isDone = false;

	SDL_Event event;
	Window window;
	
	FlockerState flock(10, 5, 5);
	
	while( !isDone )
	{
		while(SDL_PollEvent(&event))
		{
			if(event.type == SDL_QUIT)
			{
				isDone = true;
			}
			flock.HandleEvents(event);
		}

		Timer::Instance().Update();
		flock.Update();

		SDL_RenderClear(window.GetRenderer());
		flock.Render(window.GetRenderer());
		SDL_RenderPresent(window.GetRenderer());
	}

	return 0;
}
