#ifndef TEXTURE_FLYWEIGHT_H
#define TEXTURE_FLYWEIGHT_H

#include <unordered_map>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

class TextureFlyweight
{
public:
	TextureFlyweight(const TextureFlyweight& ) = delete;
	TextureFlyweight(const TextureFlyweight&&) = delete;
	TextureFlyweight& operator = (const TextureFlyweight&) = delete;
	TextureFlyweight& operator = (const TextureFlyweight&&) = delete;
	~TextureFlyweight();

	static TextureFlyweight& Instance();

	SDL_Texture* GetTexture(std::string spritePath);

	void SetRenderer(SDL_Renderer* newRenderer);
private:
	TextureFlyweight();
	SDL_Texture* AddTexture(std::string spritePath);

	std::unordered_map<std::string, SDL_Texture*> textures;
	SDL_Renderer* renderer;
};

#endif //TEXTURE_FLYWEIGHT_H
