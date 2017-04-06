#include "steering_object.h"

SteeringObject::SteeringObject(Vector2 position, double size)
	: Actor(Vector2{0,0}, Vector2{0,0}), 
	first{position, Vector2{size,size}, "agent.png", 1, 3, Vector2{0,0}, 200, 3},
	second{position + Vector2{100,0}, Vector2{size,size}, "agent.png", 1, 3, Vector2{0,0}, 200, 3},
	isMoving{false}, destination{position}, state{State::SEEKING}
{
}

void SteeringObject::HandleEvents(SDL_Event& event)
{
	static bool isMouseButtonPressed = false;
	if(event.type == SDL_MOUSEBUTTONDOWN)
		isMouseButtonPressed = true;
	else if(event.type == SDL_MOUSEBUTTONUP)
		isMouseButtonPressed = false;
	
	if(event.type == SDL_KEYDOWN)
	{
		isMoving = false;
		first.SetVelocity({0,0});
		second.SetVelocity({0,0});
		
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
			first.SetVelocity({1,0});
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

void SteeringObject::Update()
{
	if(isMoving)
	{
		switch(state)
		{
		case State::SEEKING:
			first.AddAcceleration(first.Seek(destination));
			break;
		case State::FLEEING:
			first.AddAcceleration(first.Flee(destination));
			break;
		case State::ARRIVAL:
			first.AddAcceleration(first.Arrive(destination, 20));
			break;
		case State::WANDERING:
			first.AddAcceleration(first.Wander(50, 50));
			break;
		case State::PURSUIT:
			second.AddAcceleration(second.Pursue(first));
			first.AddAcceleration(first.Arrive(destination, 50));
			break;
		case State::EVASION:
			second.AddAcceleration(second.Evade(first));
			first.AddAcceleration(first.Arrive(destination, 50));
			break;
		case State::FOLLOWING:
			second.AddAcceleration(second.Follow(first, 20));
			first.AddAcceleration(first.Arrive(destination, 50));
			break;
		case State::AVOIDING:
			first.AddAcceleration(first.Arrive(destination, 20));
			first.AddAcceleration(first.Avoid(second, 30, 30));
			break;
		}
	}
	
	first.Update();
	second.Update();
}

void SteeringObject::Render(SDL_Renderer* renderer)
{
	first.Render(renderer);
	second.Render(renderer);
}

