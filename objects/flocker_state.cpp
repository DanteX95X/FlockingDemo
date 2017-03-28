#include "flocker_state.h"
#include "utilities/timer.h"

FlockerState::FlockerState(double size, int rows, int columns)
	: velocity{0,0}
{
	for(int i = 0; i < rows; ++i)
		for(int j = 0; j < columns; ++j)
			agents.push_back(Agent{{320+size*i, 240+size*j}, {size,size}, "hex.png", 100, {0,0}});
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
	
	double shortestDistance = 100000;
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
	Vector2 steering = agents[index].Seek(target);
	std::cout << steering << "\n";
	for(std::size_t i = 0; i < agents.size(); ++i)
	{
		agents[i].AddAcceleration(steering);
	}
	
	
	
	for(std::size_t i = 0; i < agents.size(); ++i)
	{
		Vector2 separation = ComputeSeparation(i) * 1;
		Vector2 alignement = ComputeAlignement(i) * 1;
		Vector2 cohesion = ComputeCohesion(i) * 0.8;
		
		agents[i].AddAcceleration(separation + alignement + cohesion);
		
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
	/*Vector2 alignement{0,0};
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
	return alignement;*/
	
	Agent& agent = agents[index];
	double neighbourhood = 50;
	Vector2 result{0,0};
	int count = 0;
	for(std::size_t i = 0; i < agents.size(); ++i)
	{
		Agent& another = agents[i];
		double distance = (agent.GetPosition() - another.GetPosition()).Length();
		if(distance > 0 && distance < neighbourhood)
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
	/*Agent& agent = agents[index];
	Vector2 centerOfMass{agent.GetPosition()};
	double maxCohesion = agent.GetSize().x * 2;
	int neighbourCount = 1;
	const double maxSpeed = 1;
	//const double maxForce = 10;
	
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
	return desiredVelocity;*/
	
	Agent& agent = agents[index];
	double neighbourhood = 50;
	Vector2 centerOfMass{0,0};
	int count = 0;
	for(std::size_t i = 0; i < agents.size(); ++i)
	{
		Agent& another = agents[i];
		double distance = (agent.GetPosition() - another.GetPosition()).Length();
		if( distance > 0 && distance < neighbourhood)
		{
			centerOfMass += another.GetPosition();
			++count;
			
		}
	}
	
	if(count > 0)
	{
		centerOfMass /= count;
		return agent.Seek(centerOfMass); //SEEK
	}	
	return Vector2{0,0};
}

Vector2 FlockerState::ComputeSeparation(std::size_t index)
{
	/*Vector2 separation{0,0};
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
	return separation;*/
	
	const double desiredSeparation = 25;
	Vector2 steering{0,0};
	Agent& agent = agents[index];
	int count = 0;
	
	for(std::size_t i = 0; i < agents.size(); ++i)
	{
		Agent& another = agents[i];
		double distance = (agent.GetPosition() - another.GetPosition()).Length();
		if(distance > 0 && distance < desiredSeparation)
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