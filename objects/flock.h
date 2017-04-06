#ifndef FLOCK_H
#define FLOCK_H

#include <vector>
#include "agent.h"
#include "actor.h"

class Flock : public Actor
{
	enum class State
	{
		SEEKING,
		FLEEING,
		ARRIVAL,
		WANDERING,
		PURSUIT,
		EVASION,
		FOLLOWING,
		AVOIDING,
	};
	
public:
	Flock
	(
		Vector2 position, double size, unsigned int agentsInRow, unsigned int agentsInColumn, 
		double initSeekingWeight, double initSeparationWeight, double initAlignementWeight, double initCohesionWeight, double initProximityTolerance
	);
	
	void Update() override;
	void HandleEvents(SDL_Event& event) override;
	void Render(SDL_Renderer* renderer) override;
	
	const std::vector<Agent>& GetAgents();
	
	Vector2 SeekFlockDestination();
	Vector2 Seek(Agent& agent, Vector2 target);
	Vector2 ComputeAlignement(Agent& agent);
	Vector2 ComputeCohesion(Agent& agent);
	Vector2 ComputeSeparation(Agent& agent);
private:
	std::vector<Agent> agents;
	Vector2 velocity;
	
	bool isMoving;
	Vector2 destination;
	
	const double seekingWeight;
	const double separationWeight;
	const double alignementWeight;
	const double cohesionWeight;
	const double proximityTolerance;
	
	State state;
};


#endif //FLOCK_H