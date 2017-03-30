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
	Vector2 seeking{0,0};
	
	if(isMoving)
	{
		Vector2 centerOfMass{0,0};
		int count = 0;
		for(Agent& agent : agents)
		{
			centerOfMass += agent.GetPosition();
			++count;
		}
		centerOfMass /= count;
		
		if((destination - centerOfMass).Length() < proximityTolerance)
		{
			isMoving = false;
		}
		
		double shortestDistance = INT_MAX;
		Agent* closestToCenterOfMass = nullptr;
		for(Agent& agent : agents)
		{
			double distance = (agent.GetPosition() - centerOfMass).Length();
			if( distance < shortestDistance)
			{
				shortestDistance = distance;
				closestToCenterOfMass = &agent;
			}
		}
		
		seeking = Seek(*closestToCenterOfMass, destination);
		
	}
	for(Agent& agent : agents)
	{
		if(isMoving)
		{
			Vector2 separation = ComputeSeparation(agent);
			Vector2 alignement = ComputeAlignement(agent);
			Vector2 cohesion = ComputeCohesion(agent);
			
			agent.AddAcceleration(seeking * seekingWeight);
			agent.AddAcceleration(separation * separationWeight);
			agent.AddAcceleration(alignement * alignementWeight);
			agent.AddAcceleration(cohesion * cohesionWeight);
		}
		else
		{
			agent.SetVelocity({0,0});
		}
		agent.Update();
	}
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
	Vector2 desiredVelocity = (target - agent.GetPosition()).Normalize() * agent.GetMaxSpeed();
	Vector2 steering = desiredVelocity - agent.GetVelocity();
	if(steering.Length() > agent.GetMaxForce())
	{
		steering *= agent.GetMaxForce()/ steering.Length();
	}
	return steering;
}

Vector2 Flock::ComputeAlignement(Agent& agent)
{	
	Vector2 result{0,0};
	int count = 0;
	for(Agent& another : agents)
	{
		double distance = (agent.GetPosition() - another.GetPosition()).Length();
		if(distance > 0 && distance < agent.GetNeighbourhoodRadius())
		{
			result += another.GetVelocity();
			++count;
		}
	}
	
	if(count > 0)
	{
		result /= count;
		result.Normalize();
		result *= agent.GetMaxSpeed();
		Vector2 steering = result - agent.GetVelocity();
		if(steering.Length() > agent.GetMaxForce())
		{
			steering *= agent.GetMaxForce() / steering.Length();
			return steering;
		}
	}
	
	return Vector2{0,0};
}

Vector2 Flock::ComputeCohesion(Agent& agent)
{	
	Vector2 centerOfMass{0,0};
	int count = 0;
	for(Agent& another : agents)
	{
		double distance = (agent.GetPosition() - another.GetPosition()).Length();
		if( distance > 0 && distance < agent.GetNeighbourhoodRadius())
		{
			centerOfMass += another.GetPosition();
			++count;
		}
	}
	
	if(count > 0)
	{
		centerOfMass /= count;
		return Seek(agent, centerOfMass);
	}	
	return Vector2{0,0};
}

Vector2 Flock::ComputeSeparation(Agent& agent)
{	
	Vector2 steering{0,0};
	int count = 0;
	
	for(Agent& another : agents)
	{
		double distance = (agent.GetPosition() - another.GetPosition()).Length();
		if(distance > 0 && distance < agent.GetSeparationRadius())
		{
			Vector2 difference = (agent.GetPosition() - another.GetPosition()).Normalize() / distance;
			steering += difference;
			++count;
		}
	}
	
	if(count > 0)
		steering /= count;
	
	if(steering.Length() > 0)
	{
		steering.Normalize();
		steering *= agent.GetMaxSpeed();
		steering -= agent.GetVelocity();
		
		if(steering.Length() > agent.GetMaxForce())
			steering *= agent.GetMaxForce() / steering.Length();
	}
	return steering;
}

const std::vector<Agent>& Flock::GetAgents() { return agents; }