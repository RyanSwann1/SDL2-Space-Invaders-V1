#include "Media.h"
#include "Display.h"


Media::Media()
{
}


Media::~Media()
{
}

bool Media::load(Display & display)
{
	bool success = true;

	m_laser = loadTexture(display, "laser.bmp");
	if (m_laser == nullptr)
	{
		printf("Failed to load laser.", SDL_GetError());
		success = false;
	}

	m_player = loadTexture(display, "player.bmp");
	if (m_player == nullptr)
	{
		printf("Failed to load player", SDL_GetError());
		success = false;
	}

	m_enemy = loadTexture(display, "enemy.bmp");
	if (m_enemy == nullptr)
	{
		printf("Failed to load enemy", SDL_GetError());
		success = false;
	}
	return success;
}

SDL_Surface * Media::loadSurface(Display & display, std::string path)
{
		SDL_Surface* optimizedSurface = nullptr;
		SDL_Surface* surface = SDL_LoadBMP(path.c_str());
		if(surface == nullptr)
		{
			printf("Unable to load", path.c_str(), SDL_GetError());
		}
		else
		{
			optimizedSurface = SDL_ConvertSurface(surface, display.getWindowSurface()->format, 0);
		}
		SDL_FreeSurface(surface);
		return optimizedSurface;
}

SDL_Texture * Media::loadTexture(Display& display, std::string path)
{
	SDL_Texture* texture = SDL_CreateTextureFromSurface(display.getRenderer(), loadSurface(display, path.c_str()));
	if (texture == nullptr)
	{
		printf("Failed to get texture.", SDL_GetError());
	}
	return texture;
}
