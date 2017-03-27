#include "flocker_state.h"


FlockerState::FlockerState()
{
	agents.push_back(Agent{{320,240}, {10, 10}, "hex.png", 100, {0,0}});
	agents.push_back(Agent{{330,240}, {10, 10}, "hex.png", 100, {0,0}});
	agents.push_back(Agent{{320,250}, {10, 10}, "hex.png", 100, {0,0}});
	agents.push_back(Agent{{330,250}, {10, 10}, "hex.png", 100, {0,0}});
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
	for(Agent& agent : agents)
	{
		agent.Update(*this);
	}
	
	for(std::size_t i = 0; i < agents.size(); ++i)
	{
		Vector2 alignement = ComputeAlignement(i);
		Vector2 cohesion = ComputeCohesion(i);
		Vector2 separation = ComputeSeparation(i);
		Vector2 newVelocity = alignement + cohesion + separation;
		//newVelocity.Normalize();
		agents[i].SetVelocity(newVelocity);
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
	Vector2 alignement{0,0};
	int neighbourCount = 0;
	for(std::size_t i = 0; i < agents.size(); ++i)
	{
		if(index != i)
		{
			if(agents[index].IsInRange(agents[i].GetPosition()))
			{
				alignement += agents[i].GetVelocity();
				++neighbourCount;
			}
		}
	}
	
	if(neighbourCount > 0)
		alignement /= neighbourCount;
		
	return alignement;
}

Vector2 FlockerState::ComputeCohesion(std::size_t index)
{
	Vector2 centerOfMass{0,0};
	int neighbourCount = 0;
	for(std::size_t i = 0; i < agents.size(); ++i)
	{
		if(index != i)
		{
			if(agents[index].IsInRange(agents[i].GetPosition()))
			{
				centerOfMass += agents[i].GetPosition();
				++neighbourCount;
			}
		}
	}
	
	if(neighbourCount > 0)
		centerOfMass /= neighbourCount;
		
	Vector2 cohesion = centerOfMass - agents[index].GetPosition();
	return cohesion;
}

Vector2 FlockerState::ComputeSeparation(std::size_t index)
{
	Vector2 separation{0,0};
	int neighbourCount = 0;
	
	for(std::size_t i = 0; i < agents.size(); ++i)
	{
		if(index != i)
		{
			if(agents[index].IsInRange(agents[i].GetPosition()))
			{
				separation += agents[index].GetPosition() - agents[i].GetPosition();
				++neighbourCount;
			}
		}
	}
	
	if(neighbourCount > 0)
		separation /= neighbourCount;
	
	return separation;
}

const std::vector<Agent>& FlockerState::GetAgents() { return agents; }