#include "prop.h"
#include "../utilities/texture_flyweight.h"

Prop::Prop(Vector2 initPosition, Vector2 initSize, std::string spritePath)
	: Object(initPosition, initSize), texture{TextureFlyweight::Instance().GetTexture(spritePath)}
{
}

Prop::Prop(std::string spritePath)
	: Object({0,0}, {0,0}), texture{TextureFlyweight::Instance().GetTexture(spritePath)}
{
}
Prop::Prop(Vector2 initPosition, Vector2 initSize)
    : Object(initPosition, initSize)
{
}

void Prop::Render(SDL_Renderer* renderer)
{
	SDL_Rect destination = { static_cast<int>(position.x), static_cast<int>(position.y), static_cast<int>(size.x), static_cast<int>(size.y) };
	SDL_RenderCopy(renderer, texture, nullptr, &destination);
}

Vector2 Prop::GetPosition() { return Object::GetPosition(); }
Vector2 Prop::GetSize() { return Object::GetSize(); }


void Prop::SetTexture(SDL_Texture* texture) { this->texture = texture; }

SDL_Texture* Prop::GetTexture() { return texture; }
