#include "flocker_state.h"
#include "utilities/timer.h"

FlockerState::FlockerState(double size, int rows, int columns)
{
	for(int i = 0; i < rows; ++i)
		for(int j = 0; j < columns; ++j)
			agents.push_back(Agent{{320+size*i, 240+size*j}, {size,size}, "hex.png", 40, {0,0}});
}

void FlockerState::HandleEvents(SDL_Event& event)
{
	for(Agent& agent : agents)
	{
		agent.HandleEvents(event, *this);
	}
	
	/*if(event.type == SDL_MOUSEBUTTONDOWN)
	{	
		int x, y;
		SDL_GetMouseState(&x, &y);
		Vector2 target{static_cast<double>(x),static_cast<double>(y)};
		Vector2 velocity = target - agents[0].GetPosition();
		velocity.Normalize();
		agents[0].SetVelocity(velocity);
	}*/
}

void FlockerState::Update()
{
	/*for(Agent& agent : agents)
	{
		agent.Update(*this);
	}*/
	
	for(std::size_t i = 0; i < agents.size(); ++i)
	{
		Vector2 alignement = ComputeAlignement(i);
		Vector2 cohesion = ComputeCohesion(i);
		Vector2 separation = ComputeSeparation(i);
		Vector2 newVelocity = agents[i].GetVelocity() + (alignement + cohesion + separation);//*Timer::Instance().GetDeltaTime();
		newVelocity.Normalize();
		agents[i].SetVelocity(newVelocity);
		std::cout << i << " " << newVelocity << "\n";
		
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
	alignement.Normalize();
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
	cohesion.Normalize();
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
	separation.Normalize();
	return separation;
}

const std::vector<Agent>& FlockerState::GetAgents() { return agents; }