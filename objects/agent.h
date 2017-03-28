#ifndef AGENT_H
#define AGENT_H

#include "actor.h"
#include <set>

class Agent : public Actor
{
public:
	Agent(Vector2 initPosition, Vector2 initSize, std::string spritePath, double initRadius, Vector2 initVelocity = Vector2{0,0});
	~Agent();
	
	void HandleEvents(SDL_Event& event, State& state) override;
	void Update(State& state) override;
	
	bool IsInRange(Vector2 point);
	
	Vector2 GetVelocity();
	void SetVelocity(Vector2 newVelocity);
	
	double GetRadius();
	
private:
	Vector2 velocity;
	double radius;
};

#endif //AGENT_H