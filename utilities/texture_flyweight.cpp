#include "texture_flyweight.h"
#include <iostream>
#include <assert.h>

TextureFlyweight::TextureFlyweight()
	: textures(), renderer{nullptr}
{
}

TextureFlyweight::~TextureFlyweight()
{
	for(auto pair : textures)
		SDL_DestroyTexture(pair.second);
}

TextureFlyweight& TextureFlyweight::Instance()
{
	static TextureFlyweight instance;
	return instance;
}

SDL_Texture* TextureFlyweight::GetTexture(std::string spritePath)
{
	std::size_t texturesCount = textures.count(spritePath);
	
	if(texturesCount <= 0)
	{
		std::cout << "Loading new sprite\n";
		AddTexture(spritePath);
	}
	
	return textures[spritePath];
}

SDL_Texture* TextureFlyweight::AddTexture(std::string spritePath)
{
	SDL_Surface* surface;
	surface = IMG_Load(spritePath.c_str());
	assert(surface != nullptr);

	SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
	assert(texture != nullptr);
	SDL_FreeSurface(surface);

	textures[spritePath] = texture;
	
	return textures[spritePath];
}

void TextureFlyweight::SetRenderer(SDL_Renderer* newRenderer) { renderer = newRenderer; }