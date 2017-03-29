#include "agent.h"
#include "utilities/timer.h"
#include <iostream>
#include "flocker_state.h"

#define _USE_MATH_DEFINES //for M_PI constant
#include <math.h>

Agent::Agent(Vector2 initPosition, Vector2 initSize, std::string spritePath, double initRadius, Vector2 initVelocity)
	: Actor(initPosition, initSize, spritePath), velocity{initVelocity}, acceleration{0,0}, radius{initRadius}, maxSpeed{200}, maxForce{3}, angle{0}
{
}

Agent::~Agent()
{
}

void Agent::Update(State& state)
{
	FlockerState* flock = static_cast<FlockerState*>(&state);
	std::vector<Agent> agents = flock->GetAgents();
	
	angle = atan2(velocity.y, velocity.x) * 180 / M_PI + 90;
	
	velocity += acceleration;
	double magnitude = velocity.Length();
	if( magnitude > maxSpeed)
	{
		velocity *= maxSpeed / magnitude;
	}
	
	position += velocity * Timer::Instance().GetDeltaTime();
	acceleration *= 0;
	
	if(position.x < 0)
		position.x = 1280 + position.x;
	else if(position.x > 1280)
		position.x = position.x - 1280;
	
	if(position.y < 0)
		position.y = 720 + position.y;
	else if(position.y > 720)
		position.y = position.y - 720;
}

void Agent::HandleEvents(SDL_Event& event, State& state)
{
	FlockerState* flock = static_cast<FlockerState*>(&state);
	std::vector<Agent> agents = flock->GetAgents();
	
}

void Agent::Render(SDL_Renderer* renderer)
{
	SDL_Rect destination = { static_cast<int>(position.x-size.x/2), static_cast<int>(position.y-size.y/2), static_cast<int>(size.x), static_cast<int>(size.y) };
	SDL_RenderCopyEx(renderer, texture, nullptr, &destination, angle, nullptr, SDL_FLIP_NONE);
}

bool Agent::IsInRange(Vector2 point)
{
	return (point.x - position.x)*(point.x - position.x) + (point.y - position.y)*(point.y - position.y) < radius*radius;
}

Vector2 Agent::Seek(Vector2 target)
{
	Vector2 desiredVelocity = (target - position).Normalize() * maxSpeed;
	Vector2 steering = desiredVelocity - velocity;
	if(steering.Length() > maxForce)
	{
		steering *= maxForce / steering.Length();
	}
	return steering;
}

Vector2 Agent::GetVelocity() { return velocity; }
void Agent::SetVelocity(Vector2 newVelocity) { velocity = newVelocity; }

double Agent::GetRadius() { return radius; }

const double Agent::GetMaxSpeed() { return maxSpeed; }
const double Agent::GetMaxForce() { return maxForce; }

Vector2 Agent::GetAcceleration() { return acceleration; }
void Agent::AddAcceleration(Vector2 increase) { acceleration += increase; }