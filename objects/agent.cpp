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
	Vector2 desiredVelocity = (target - position).Normalize() * maxSpeed;
	Vector2 steering = desiredVelocity - velocity;
	steering.Limit(maxForce);
	return steering;
}

Vector2 Agent::Flee(Vector2 target) const
{
	Vector2 desiredVelocity = (position - target).Normalize() * maxSpeed;
	Vector2 steering = desiredVelocity - velocity;
	steering.Limit(maxForce);
	return steering;
}

Vector2 Agent::Arrive(Vector2 target, const double slowingRadius) const
{
	Vector2 desiredVelocity = target - position;
	double distance = desiredVelocity.Length();
	
	if(distance < slowingRadius)
	{
		desiredVelocity = desiredVelocity.Normalize() * maxSpeed * (distance / slowingRadius);
	}
	else
	{
		desiredVelocity = desiredVelocity.Normalize() * maxSpeed;
	}
	
	Vector2 steering = desiredVelocity - velocity;
	steering.Limit(maxForce);
	return steering;
}

Vector2 Agent::Wander(double circleDistance, double circleRadius) const
{
	Vector2 center = velocity;
	center.Normalize();
	center *= circleDistance;
	
	Vector2 displacement = velocity;
	displacement.Normalize();
	displacement *= circleRadius;
	
	double angle = rand()%360 - 180;
	
	displacement = displacement.Rotate(angle);
	
	Vector2 steering = displacement + center;
	steering.Limit(maxForce);
	return steering;
}

Vector2 Agent::Pursue(Agent& agent) const
{
	int expectedTime = (position - agent.GetPosition()).Length() / agent.GetMaxSpeed();
	Vector2 futurePosition = agent.GetPosition() + agent.GetVelocity() * expectedTime;
	return Seek(futurePosition);
}

Vector2 Agent::Evade(Agent& agent) const
{
	int expectedTime = (position - agent.GetPosition()).Length() / agent.GetMaxSpeed();
	Vector2 futurePosition = agent.GetPosition() + agent.GetVelocity() * expectedTime;
	return Flee(futurePosition);
}

Vector2 Agent::Follow(Agent& agent, double distance, double arrivalRadius) const
{	
	const double sightRadius = agent.GetSize().x;
	Vector2 displacement = -agent.GetVelocity();
	displacement.Normalize();
	displacement *= distance;
	Vector2 behindLeader = agent.GetPosition() + displacement;
	Vector2 aheadLeader = agent.GetPosition() + displacement*(-1);
	
	Vector2 steering{0,0};
	if( (agent.GetPosition() - position).Length() < sightRadius ||  (aheadLeader - position).Length() < sightRadius )
	{
		steering += Evade(agent);
	}
	
	steering += Arrive(behindLeader, arrivalRadius);
	return steering;
}

Vector2 Agent::Avoid(Agent& agent, double distance, double maxAvoidForce) const
{
	Vector2 displacement = velocity;
	displacement.Normalize();
	displacement *= distance;
	
	Vector2 ahead = position + displacement;
	Vector2 steering{0,0};

	if( pow(ahead.x - agent.GetPosition().x, 2) + pow(ahead.y - agent.GetPosition().y, 2) < pow(agent.GetSize().x/2,2))
	{
		steering = (ahead - agent.GetPosition()) * maxAvoidForce;
	}
	return steering;
}

Vector2 Agent::GetVelocity() const { return velocity; } 
void Agent::SetVelocity(Vector2 newVelocity) { velocity = newVelocity; }

double Agent::GetSeparationRadius() { return separationRadius; }
double Agent::GetNeighbourhoodRadius() { return neighbourhoodRadius; }

const double Agent::GetMaxSpeed() const { return maxSpeed; }
const double Agent::GetMaxForce() const { return maxForce; }

Vector2 Agent::GetAcceleration() { return acceleration; }
void Agent::AddAcceleration(Vector2 increase) { acceleration += increase; }