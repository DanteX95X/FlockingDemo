#include "flocker_state.h"


FlockerState::FlockerState()
{
	agents.push_back(Agent{{100,100}, {30, 30}, "hex.png", {100,0}});
	agents.push_back(Agent{{100,100}, {30, 30}, "hex.png", {0,100}});
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
	for(Agent& agent : agents)
	{
		agent.Update(*this);
	}
}

void FlockerState::Render(SDL_Renderer* renderer)
{
	for(Agent& agent : agents)
	{
		agent.Render(renderer);
	}
}

const std::vector<Agent>& FlockerState::GetAgents() { return agents; }