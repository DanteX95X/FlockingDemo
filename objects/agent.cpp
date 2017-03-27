#include "agent.h"
#include "utilities/timer.h"
#include <iostream>
#include "flocker_state.h"

Agent::Agent(Vector2 initPosition, Vector2 initSize, std::string spritePath, double initRadius, Vector2 initVelocity)
	: Actor(initPosition, initSize, spritePath), velocity{initVelocity}, radius{initRadius}
{
}

Agent::~Agent()
{
}

void Agent::Update(State& state)
{
	FlockerState* flock = static_cast<FlockerState*>(&state);
	std::vector<Agent> agents = flock->GetAgents();
	
	position += velocity * 100 * Timer::Instance().GetDeltaTime();
	
}

void Agent::HandleEvents(SDL_Event& event, State& state)
{
	FlockerState* flock = static_cast<FlockerState*>(&state);
	std::vector<Agent> agents = flock->GetAgents();
	
	if(event.type == SDL_MOUSEBUTTONDOWN)
	{	
		int x, y;
		SDL_GetMouseState(&x, &y);
		Vector2 target{static_cast<double>(x),static_cast<double>(y)};
		velocity = target - position;
		velocity.Normalize();
	}
}

bool Agent::IsInRange(Vector2 point)
{
	return (point.x - position.x)*(point.x - position.x) + (point.y - position.y)*(point.y - position.y) < radius*radius;
}

Vector2 Agent::GetVelocity() { return velocity; }
void Agent::SetVelocity(Vector2 newVelocity) { velocity = newVelocity; }