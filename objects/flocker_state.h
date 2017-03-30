#ifndef FLOCKER_STATE_H
#define FLOCKER_STATE_H

#include "state.h"
#include <vector>
#include "agent.h"

class FlockerState : public State
{
public:
	FlockerState
	(
		double size, int agentsInRow, int agentsInColumn, 
		double initSeekingWeight, double initSeparationWeight, double initAlignementWeight, double initCohesionWeight
	);
	
	void Update() override;
	void HandleEvents(SDL_Event& event) override;
	void Render(SDL_Renderer* renderer) override;
	
	const std::vector<Agent>& GetAgents();
	
	Vector2 ComputeAlignement(std::size_t index);
	Vector2 ComputeCohesion(std::size_t index);
	Vector2 ComputeSeparation(std::size_t index);
	Vector2 Seek(std::size_t index, Vector2 taget);
private:
	std::vector<Agent> agents;
	Vector2 velocity;
	
	const double seekingWeight;
	const double separationWeight;
	const double alignementWeight;
	const double cohesionWeight;
};


#endif //FLOCKER_STATE_H