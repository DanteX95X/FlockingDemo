#include "agent.h"
#include "utilities/timer.h"
#include <iostream>
#include "flocker_state.h"

Agent::Agent(Vector2 initPosition, Vector2 initSize, std::string spritePath, Vector2 initVelocity)
	: Actor(initPosition, initSize, spritePath), velocity{initVelocity}
{
}

Agent::~Agent()
{
}

void Agent::Update(State& state)
{
	FlockerState* flock = static_cast<FlockerState*>(&state);
	std::vector<Agent> agents = flock->GetAgents();
	
	position += velocity * Timer::Instance().GetDeltaTime();
	
}

void Agent::HandleEvents(SDL_Event& event, State& state)
{
	FlockerState* flock = static_cast<FlockerState*>(&state);
	std::vector<Agent> agents = flock->GetAgents();
	
	if(event.type == SDL_MOUSEBUTTONDOWN)
	{	
		velocity = Vector2{0,0};
	}
}