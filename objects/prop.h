#ifndef PROP_H
#define PROP_H

#include "object.h"
#include <string>
#include <SDL2/SDL.h>

class Prop : public Object
{
public:
	Prop(Vector2 initPosition, Vector2 initSize, std::string spritePath);
	Prop(std::string spritePath);
    Prop(Vector2 initPosition, Vector2 initSize);

	virtual void Update() = 0;
	virtual void Render(SDL_Renderer* renderer);

	Vector2 GetPosition();
	Vector2 GetSize();

    void SetTexture(SDL_Texture*);
	SDL_Texture* GetTexture();
	
protected:
	SDL_Texture* texture;

};

#endif //PROP_H
