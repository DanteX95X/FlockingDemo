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
	  alignementWeight{initAlignementWeight}, cohesionWeight{initCohesionWeight}, proximityTolerance{initProximityTolerance},
	  state{State::SEEKING}
{
	position -= {size*agentsInRow/2, size*agentsInColumn/2};
	/*for(std::size_t i = 0; i < agentsInRow; ++i)
		for(std::size_t j = 0; j < agentsInColumn; ++j)
			agents.push_back(Agent{{position.x+size*i, position.y+size*j}, {size,size}, "agent.png", 1, 3, {0,0}, 200, 3});
			
	assert(agents.size() > 0);*/
	agents.push_back(Agent{position, {size,size}, "agent.png", 1, 3, {0,0}, 200, 3});
	agents.push_back(Agent{position + Vector2{100, 100}, {size,size}, "agent.png", 1, 3, {0,0}, 200, 3});
}

void Flock::HandleEvents(SDL_Event& event)
{
	static bool isMouseButtonPressed = false;
	if(event.type == SDL_MOUSEBUTTONDOWN)
		isMouseButtonPressed = true;
	else if(event.type == SDL_MOUSEBUTTONUP)
		isMouseButtonPressed = false;
	
	if(event.type == SDL_KEYDOWN)
	{
		isMoving = false;
		for(Agent& agent : agents)
		{
			agent.SetVelocity({0,0});
		}
		switch(event.key.keysym.sym)
		{
		case SDLK_1:
			std::cout << "Seeking\n";
			state = State::SEEKING;
			break;
		case SDLK_2:
			std::cout << "Fleeing\n";
			state = State::FLEEING;
			break;
		case SDLK_3:
			state = State::ARRIVAL;
			std::cout << "Arrival\n";
			break;
		case SDLK_4:
			state = State::WANDERING;
			agents[0].SetVelocity({1,0});
			std::cout << "Wandering\n";
			break;
		case SDLK_5:
			state = State::PURSUIT;
			std::cout << "Pursuit\n";
			break;
		case SDLK_6:
			state = State::EVASION;
			std::cout << "Evasion\n";
			break;
		case SDLK_7:
			state = State::FOLLOWING;
			std::cout << "Following\n";
			break;
		case SDLK_8:
			state = State::AVOIDING;
			std::cout << "Avoiding\n";
			break;
		}
	}
	
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
	//Vector2 seeking = SeekFlockDestination();
	
	if(isMoving)
	{
		switch(state)
		{
		case State::SEEKING:
			agents[0].AddAcceleration(agents[0].Seek(destination));
			break;
		case State::FLEEING:
			agents[0].AddAcceleration(agents[0].Flee(destination));
			break;
		case State::ARRIVAL:
			agents[0].AddAcceleration(agents[0].Arrive(destination, 20));
			break;
		case State::WANDERING:
			agents[0].AddAcceleration(agents[0].Wander(50, 50));
			break;
		case State::PURSUIT:
			agents[1].AddAcceleration(agents[1].Pursue(agents[0]));
			agents[0].AddAcceleration(agents[0].Arrive(destination, 50));
			break;
		case State::EVASION:
			agents[1].AddAcceleration(agents[1].Evade(agents[0]));
			agents[0].AddAcceleration(agents[0].Arrive(destination, 50));
			break;
		case State::FOLLOWING:
			agents[1].AddAcceleration(agents[1].Follow(agents[0], 20));
			agents[0].AddAcceleration(agents[0].Arrive(destination, 50));
			break;
		case State::AVOIDING:
			agents[0].AddAcceleration(agents[0].Arrive(destination, 20));
			agents[0].AddAcceleration(agents[0].Avoid(agents[1], 30, 30));
			break;
		}
	}
	
	for(Agent& agent : agents)
	{
		/*if(isMoving)
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
		}*/
		
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
	if(!isMoving)
	{
		return Vector2{0,0};
	}
	
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
	
	return closestToCenterOfMass->Arrive(destination, 100);
}

Vector2 Flock::ComputeAlignement(Agent& agent)
{	
	Vector2 resultant{0,0};
	int count = 0;
	for(Agent& another : agents)
	{
		double distance = (agent.GetPosition() - another.GetPosition()).Length();
		if(distance > 0 && distance < agent.GetNeighbourhoodRadius())
		{
			resultant += another.GetVelocity();
			++count;
		}
	}
	
	if(count > 0)
	{
		resultant /= count;
		resultant.Normalize();
		resultant *= agent.GetMaxSpeed();
		Vector2 steering = resultant - agent.GetVelocity();
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
		return agent.Seek(centerOfMass);
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