#ifndef AGENT_H
#define AGENT_H

#include "actor.h"

class Agent : public Actor
{
public:
	Agent
	(
		Vector2 initPosition, Vector2 initSize, std::string spritePath, 
		double separationRadiusCoefficient, double neighbourhoodRadiusCoefficient, Vector2 initVelocity,
		double initMaxSpeed, double initMaxForce
	);
	~Agent();
	
	void HandleEvents(SDL_Event& event) override;
	void Update() override;
	void Render(SDL_Renderer* renderer) override;

	Vector2 Seek(Vector2 target) const;
	Vector2 Flee(Vector2 target) const;
	Vector2 Arrive(Vector2 target, const double slowingRadius) const;
	Vector2 Wander(double circleDistance, double circleRadius) const;
	Vector2 Pursue(Agent& agent) const;
	Vector2 Evade(Agent& agent) const;
	Vector2 Follow(Agent& agent, double distance) const;
	Vector2 Avoid(Agent& agent, double distance, double maxAvoidForce) const;
	
	Vector2 GetVelocity() const;
	void SetVelocity(Vector2 newVelocity);
	
	double GetSeparationRadius();
	double GetNeighbourhoodRadius();
	const double GetMaxSpeed() const;
	const double GetMaxForce() const;
	
	Vector2 GetAcceleration();
	void AddAcceleration(Vector2 increase);
	
private:
	Vector2 velocity;
	Vector2 acceleration;
	
	const double separationRadius;
	const double neighbourhoodRadius;
	const double maxSpeed;
	const double maxForce;
	
	double angle;
};

#endif //AGENT_H