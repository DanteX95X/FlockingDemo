#include "actor.h"
#include<iostream>
#include<math.h>
#include "../utilities/texture_flyweight.h"

Actor::Actor(Vector2 initPosition, Vector2 initSize, std::string spritePath)
	: Prop(initPosition, initSize, spritePath)
{
}

Actor::Actor(Vector2 initPosition, Vector2 initSize)
	: Prop(initPosition, initSize)
{
}

bool Actor::IsMouseInside(Vector2 clickPosition, Vector2 midPosition, double side)
{
    return ( pow((clickPosition.x-midPosition.x),2) + pow((clickPosition.y - midPosition.y),2) < pow(side/2 - side/10,2 ) );
}
