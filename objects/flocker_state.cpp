#include "flocker_state.h"
#include "../utilities/timer.h"
#include <climits>

FlockerState::FlockerState
(
	double size, int agentsInRow, int agentsInColumn,
	double initSeekingWeight, double initSeparationWeight, double initAlignementWeight, double initCohesionWeight
)
	: velocity{0,0}, 
	  seekingWeight{initSeekingWeight}, separationWeight{initSeparationWeight}, 
	  alignementWeight{initAlignementWeight}, cohesionWeight{initCohesionWeight} 
{
	for(int i = 0; i < agentsInRow; ++i)
		for(int j = 0; j < agentsInColumn; ++j)
			agents.push_back(Agent{{320+size*i, 240+size*j}, {size,size}, "agent.png", 1, 3, {0,0}, 200, 3});
}

void FlockerState::HandleEvents(SDL_Event& event)
{
	for(Agent& agent : agents)
	{
		agent.HandleEvents(event, *this);
	}
}

void FlockerState::Update()
{	
	Vector2 centerOfMass{0,0};
	int count = 0;
	for(std::size_t i = 0; i < agents.size(); ++i)
	{
		centerOfMass += agents[i].GetPosition();
		++count;
	}
	centerOfMass /= count;
	
	double shortestDistance = INT_MAX;
	std::size_t index = -1;
	for(std::size_t i = 0; i < agents.size(); ++i)
	{
		double distance = (agents[i].GetPosition() - centerOfMass).Length();
		if( distance < shortestDistance)
		{
			shortestDistance = distance;
			index = i;
		}
	}
	
	int x, y;
	SDL_GetMouseState(&x, &y);
	Vector2 target{static_cast<double>(x),static_cast<double>(y)};
	Vector2 seeking = agents[index].Seek(target);
	
	for(std::size_t i = 0; i < agents.size(); ++i)
	{
		Vector2 separation = ComputeSeparation(i);
		Vector2 alignement = ComputeAlignement(i);
		Vector2 cohesion = ComputeCohesion(i);
		
		agents[i].AddAcceleration(seeking * seekingWeight);
		agents[i].AddAcceleration(separation * separationWeight);
		agents[i].AddAcceleration(alignement * alignementWeight);
		agents[i].AddAcceleration(cohesion * cohesionWeight);
		
		agents[i].Update(*this);
	}
}

void FlockerState::Render(SDL_Renderer* renderer)
{
	for(Agent& agent : agents)
	{
		agent.Render(renderer);
	}
}

Vector2 FlockerState::ComputeAlignement(std::size_t index)
{	
	Agent& agent = agents[index];
	Vector2 result{0,0};
	int count = 0;
	for(std::size_t i = 0; i < agents.size(); ++i)
	{
		Agent& another = agents[i];
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

Vector2 FlockerState::ComputeCohesion(std::size_t index)
{	
	Agent& agent = agents[index];
	Vector2 centerOfMass{0,0};
	int count = 0;
	for(std::size_t i = 0; i < agents.size(); ++i)
	{
		Agent& another = agents[i];
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
		return agent.Seek(centerOfMass);
	}	
	return Vector2{0,0};
}

Vector2 FlockerState::ComputeSeparation(std::size_t index)
{	
	Vector2 steering{0,0};
	Agent& agent = agents[index];
	int count = 0;
	
	for(std::size_t i = 0; i < agents.size(); ++i)
	{
		Agent& another = agents[i];
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

const std::vector<Agent>& FlockerState::GetAgents() { return agents; }