#include "window/window.h"
#include "utilities/timer.h"
#include "objects/agent.h"
#include "objects/flock.h"
#include <stdlib.h>
#include <time.h>

int main(int argc, char** argv)
{	
	srand(time(nullptr));
	
	bool isDone = false;
	const int width = 1280;
	const int height = 720;

	SDL_Event event;
	Window window(width, height);
	
	Flock flock({width/2, height/2}, 19, 10, 10, 0.9, 1, 1, 0.7, 7);
	
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
