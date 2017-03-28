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
	Vector2 Seek(Vector2 target);
	
	Vector2 GetVelocity();
	void SetVelocity(Vector2 newVelocity);
	
	double GetRadius();
	const double GetMaxSpeed();
	const double GetMaxForce();
	
	Vector2 GetAcceleration();
	void AddAcceleration(Vector2 increase);
	
private:
	Vector2 velocity;
	Vector2 acceleration;
	double radius;
	const double maxSpeed;
	const double maxForce;
};

#endif //AGENT_H