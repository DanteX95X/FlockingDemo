#include "flock.h"
#include "../utilities/timer.h"
#include <climits>
#include <assert.h>

Flock::Flock
(
	Vector2 position, double size, unsigned int agentsInRow, unsigned int agentsInColumn,
	double initSeekingWeight, double initSeparationWeight, double initAlignementWeight, double initCohesionWeight, double initProximityTolerance
)
	: Actor({0,0}, {0,0}),
	  velocity{0,0}, isMoving{false}, destination{position},
	  seekingWeight{initSeekingWeight}, separationWeight{initSeparationWeight}, 
	  alignementWeight{initAlignementWeight}, cohesionWeight{initCohesionWeight}, proximityTolerance{initProximityTolerance}
{
	position -= {size*agentsInRow/2, size*agentsInColumn/2};
	for(std::size_t i = 0; i < agentsInRow; ++i)
		for(std::size_t j = 0; j < agentsInColumn; ++j)
			agents.push_back(Agent{{position.x+size*i, position.y+size*j}, {size,size}, "agent.png", 1, 3, {0,0}, 200, 3});
			
	assert(agents.size() > 0);
}

void Flock::HandleEvents(SDL_Event& event)
{
	static bool isMouseButtonPressed = false;
	if(event.type == SDL_MOUSEBUTTONDOWN)
		isMouseButtonPressed = true;
	else if(event.type == SDL_MOUSEBUTTONUP)
		isMouseButtonPressed = false;
	
	if(isMouseButtonPressed)
	{
		int x, y;
		SDL_GetMouseState(&x, &y);
		destination = {static_cast<double>(x),static_cast<double>(y)};
		isMoving = true;
	}
}

void Flock::Update()
{

}

void Flock::Render(SDL_Renderer* renderer)
{
	for(Agent& agent : agents)
	{
		agent.Render(renderer);
	}
}


Vector2 Flock::SeekFlockDestination()
{
	return Vector2{0,0};
}

Vector2 Flock::Seek(Agent& agent, Vector2 target)
{
	return Vector2{0,0};
}

Vector2 Flock::ComputeAlignement(Agent& agent)
{
	return Vector2{0,0};
}

Vector2 Flock::ComputeCohesion(Agent& agent)
{
	return Vector2{0,0};
}

Vector2 Flock::ComputeSeparation(Agent& agent)
{
	return Vector2{0,0};
}

const std::vector<Agent>& Flock::GetAgents() { return agents; }