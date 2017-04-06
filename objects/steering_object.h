#ifndef STEERING_OBJECT_H
#define STEERING_OBJECT_H

#include "agent.h"
#include "../utilities/vector2.h"

class SteeringObject : Actor
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
	SteeringObject(Vector2 position, double size);
	
	void Update() override;
	void HandleEvents(SDL_Event& event) override;
	void Render(SDL_Renderer* renderer) override;
	
private:
	Agent first;
	Agent second;
	
	bool isMoving;
	Vector2 destination;
	
	State state;
};

#endif //STEERING_OBJECT_H