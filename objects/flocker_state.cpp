#include "flocker_state.h"
#include "utilities/timer.h"

FlockerState::FlockerState(double size, int rows, int columns)
	: velocity{0,0}
{
	for(int i = 0; i < rows; ++i)
		for(int j = 0; j < columns; ++j)
			agents.push_back(Agent{{320+size*i, 240+size*j}, {size,size}, "hex.png", 100, {0,0}});
	//agents.push_back(Agent{{330, 230}, {size,size}, "hex.png", 40, {0,0}});
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
	for(std::size_t i = 0; i < agents.size(); ++i)
	{
		Vector2 separation = ComputeSeparation(i);
		Vector2 cohesion = ComputeCohesion(i);
		Vector2 velocity = agents[i].GetVelocity();
		agents[i].SetVelocity(velocity + (separation + cohesion)*Timer::Instance().GetDeltaTime());
	}
	
	for(std::size_t i = 0; i < agents.size(); ++i)
	{
		agents[i].Update(*this);
	}
	
	/*for(std::size_t i = 0; i < agents.size(); ++i)
	{
		Vector2 alignement = ComputeAlignement(i);
		Vector2 cohesion = ComputeCohesion(i);
		Vector2 separation = ComputeSeparation(i);
		Vector2 newVelocity = agents[i].GetVelocity() + (alignement + cohesion + separation);//Timer::Instance().GetDeltaTime();
		newVelocity.Normalize();
		agents[i].SetVelocity(newVelocity*100);
		std::cout << i << " " << newVelocity << "\n";
		
		agents[i].Update(*this);
	}*/
}

void FlockerState::Render(SDL_Renderer* renderer)
{
	for(Agent& agent : agents)
	{
		agent.Render(renderer);
	}
}

Vector2 FlockerState::Seek(std::size_t index, Vector2 target)
{
	const int maxSpeed = 10;
	Vector2 position = agents[index].GetPosition();
	Vector2 velocity = agents[index].GetVelocity();
	Vector2 desiredVelocity = (target - position);
	desiredVelocity *= maxSpeed / desiredVelocity.Length();
	Vector2 steering = desiredVelocity - velocity;
	
	return steering;
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
	//alignement.Normalize();
	return alignement;
}

Vector2 FlockerState::ComputeCohesion(std::size_t index)
{
	Agent& agent = agents[index];
	Vector2 centerOfMass{agent.GetPosition()};
	double maxCohesion = agent.GetSize().x * 2;
	int neighbourCount = 1;
	const double maxSpeed = 1;
	const double maxForce = 10;
	
	for(std::size_t i = 0; i < agents.size(); ++i)
	{
		if(index != i)
		{
			Agent& another = agents[i];
			double distance = (agent.GetPosition() - another.GetPosition()).Length();
			
			if( distance < maxCohesion)
			{
				centerOfMass += agents[i].GetPosition();
				++neighbourCount;
			}
		}
	}
	
	if( neighbourCount == 1)
		return Vector2{0,0};
	
	centerOfMass /= neighbourCount;
		
	//Vector2 cohesion = centerOfMass - agents[index].GetPosition();
	//cohesion.Normalize();
	Vector2 desiredVelocity = centerOfMass - agent.GetPosition();
	desiredVelocity *= maxSpeed / desiredVelocity.Length();
	
	Vector2 cohesion = desiredVelocity - agent.GetVelocity();
	cohesion.Normalize();
	return cohesion;
	//return cohesion * (maxForce / maxSpeed);
	return desiredVelocity;
}

Vector2 FlockerState::ComputeSeparation(std::size_t index)
{
	Vector2 separation{0,0};
	int neighbourCount = 0;
	Agent& agent = agents[index];
	double minSeparation = agent.GetSize().x;
	
	for(std::size_t i = 0; i < agents.size(); ++i)
	{
		if(index != i)
		{
			Agent& another = agents[i];
			double distance = (agent.GetPosition() - another.GetPosition()).Length();
			//if(agents[index].IsInRange(agents[i].GetPosition()))
			if(distance < minSeparation && distance > 0 )
			{
				separation += (agent.GetPosition() - another.GetPosition())/agent.GetRadius();
				++neighbourCount;
			}
		}
	}
	
	if(neighbourCount == 0)
		return Vector2{0,0};
	
	separation /= neighbourCount;
	//separation.Normalize();
	return separation;
}

const std::vector<Agent>& FlockerState::GetAgents() { return agents; }