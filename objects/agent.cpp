#include "agent.h"
#include "utilities/timer.h"
#include <iostream>
#include "flocker_state.h"

//change parameters
Agent::Agent(Vector2 initPosition, Vector2 initSize, std::string spritePath, double initRadius, Vector2 initVelocity)
	: Actor(initPosition, initSize, spritePath), velocity{initVelocity}, acceleration{0,0}, radius{initRadius}, maxSpeed{200}, maxForce{3}
{
	//velocity = {static_cast<double>(rand()%2000 - 1000)/10, static_cast<double>(rand()%200 - 100 )/10};
	//velocity = {static_cast<double>(100), static_cast<double>(100)};
}

Agent::~Agent()
{
}

void Agent::Update(State& state)
{
	FlockerState* flock = static_cast<FlockerState*>(&state);
	std::vector<Agent> agents = flock->GetAgents();
	
	/*int x, y;
	SDL_GetMouseState(&x, &y);
	Vector2 target{static_cast<double>(x),static_cast<double>(y)};
	std::cout << Seek(target) << "\n";
	AddAcceleration(Seek(target)*0.7);*/
	
	
	velocity += acceleration;
	double magnitude = velocity.Length();
	if( magnitude > maxSpeed)
	{
		velocity *= maxSpeed / magnitude;
	}
	
	position += velocity * Timer::Instance().GetDeltaTime();
	acceleration *= 0;
	
	if(position.x < 0)
		position.x = 640 + position.x;
	else if(position.x > 640)
		position.x = position.x - 640;
	
	if(position.y < 0)
		position.y = 480 + position.y;
	else if(position.y > 480)
		position.y = position.y - 480;
}

void Agent::HandleEvents(SDL_Event& event, State& state)
{
	FlockerState* flock = static_cast<FlockerState*>(&state);
	std::vector<Agent> agents = flock->GetAgents();
	
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