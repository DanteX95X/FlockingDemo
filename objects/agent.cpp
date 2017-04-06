#include "agent.h"
#include "../utilities/timer.h"

#define _USE_MATH_DEFINES //for M_PI constant
#include <math.h>

Agent::Agent
(
	Vector2 initPosition, Vector2 initSize, std::string spritePath, 
	double separationRadiusCoefficient, double neighbourhoodRadiusCoefficient, Vector2 initVelocity,
	double initMaxSpeed, double initMaxForce
)
	: Actor(initPosition, initSize, spritePath), 
	  velocity{initVelocity}, acceleration{0,0}, 
	  separationRadius{separationRadiusCoefficient * initSize.x * 1.41}, neighbourhoodRadius{neighbourhoodRadiusCoefficient * initSize.x * 1.41},
	  maxSpeed{initMaxSpeed}, maxForce{initMaxForce}, angle{0}
{
}

Agent::~Agent()
{
}

void Agent::Update()
{
	if(velocity.x != 0 && velocity.y != 0)
		angle = atan2(velocity.y, velocity.x) * 180 / M_PI + 90;
	
	velocity += acceleration;
	double magnitude = velocity.Length();
	if( magnitude > maxSpeed)
	{
		velocity *= maxSpeed / magnitude;
	}
	
	position += velocity * Timer::Instance().GetDeltaTime();
	acceleration *= 0;
}

void Agent::HandleEvents(SDL_Event&)
{
}

void Agent::Render(SDL_Renderer* renderer)
{
	SDL_Rect destination = { static_cast<int>(position.x-size.x/2), static_cast<int>(position.y-size.y/2), static_cast<int>(size.x), static_cast<int>(size.y) };
	SDL_RenderCopyEx(renderer, texture, nullptr, &destination, angle, nullptr, SDL_FLIP_NONE);
}


Vector2 Agent::Seek(Vector2 target) const
{
	return Vector2{0,0};
}

Vector2 Agent::Flee(Vector2 target) const
{
	return Vector2{0,0};
}

Vector2 Agent::Arrive(Vector2 target, const double slowingRadius) const
{
	return Vector2{0,0};
}

Vector2 Agent::Wander(double circleDistance, double circleRadius) const
{
	return Vector2{0,0};
}

Vector2 Agent::Pursue(Agent& agent) const
{
	return Vector2{0,0};
}

Vector2 Agent::Evade(Agent& agent) const
{
	return Vector2{0,0};
}

Vector2 Agent::Follow(Agent& agent, double distance, double arrivalRadius) const
{	
	return Vector2{0,0};
}

Vector2 Agent::Avoid(Agent& agent, double distance, double maxAvoidForce) const
{
	return Vector2{0,0};
}

Vector2 Agent::GetVelocity() const { return velocity; } 
void Agent::SetVelocity(Vector2 newVelocity) { velocity = newVelocity; }

double Agent::GetSeparationRadius() { return separationRadius; }
double Agent::GetNeighbourhoodRadius() { return neighbourhoodRadius; }

const double Agent::GetMaxSpeed() const { return maxSpeed; }
const double Agent::GetMaxForce() const { return maxForce; }

Vector2 Agent::GetAcceleration() { return acceleration; }
void Agent::AddAcceleration(Vector2 increase) { acceleration += increase; }