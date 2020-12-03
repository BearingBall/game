#pragma once
#include <string>
#include <vector>


class Texture final
{
public:
	std::string name;
	SDL_Texture* polygon;
	SDL_Rect rect;
	Texture(std::string _name, SDL_Texture* _polygon, SDL_Rect _rect)
	{
		name = _name;
		polygon = _polygon;
		rect = _rect;
	}
	~Texture() = default;
};

class Textures final
{
private:
	std::vector<Texture> textures;
public:
	Textures() = default;
	~Textures() = default;
	int addTexture(SDL_Renderer* renderer, std::string name)
	{
		for (size_t i=0;i<textures.size();++i)
		{
			if (name == textures[i].name)
			{
				return i;
			}
		}
		SDL_Surface* surface = SDL_LoadBMP(name.data());
		if (surface == nullptr)
		{
			return -1;
		}
		SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
		
		textures.emplace_back(Texture(name, texture, {0,0,surface->w,surface->h}));
		return textures.size()-1;
	}
	
	std::vector<Texture>& getTextures()
	{
		return textures;
	}
};