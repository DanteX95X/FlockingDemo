#ifndef ACTOR_H
#define ACTOR_H

#include "prop.h"

class Actor : public Prop
{
public:
    Actor(Vector2 initPosition, Vector2 initSize, std::string spritePath);
	Actor(Vector2 initPosition, Vector2 initSize);
    virtual void HandleEvents(SDL_Event& event, State& state) = 0 ;
    bool IsMouseInside(Vector2 clickPosition,Vector2 midPosition, double side);
};

#endif //ACTOR_H
