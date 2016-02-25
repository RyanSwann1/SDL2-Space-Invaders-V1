#include "Display.h"
#include "Media.h"
#include "Player.h"
#include "Enemy.h"
#include "Laser.h"


#include <iostream>
#include <vector>

Display::Display()
{
	//init();
}


Display::~Display()
{

}

bool Display::init()
{
	bool success = true;
	//Initialize SDL Video
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		success = false;
		printf("Video failed to initialize.", SDL_GetError());
	}
	else
	{
		//Create Window
		m_window = SDL_CreateWindow("Space Invaders", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
		if (m_window == nullptr)
		{
			success = false;
			printf("Failed to create window.", SDL_GetError());
		}
		else
		{
			//Get the window surface
			m_windowSurface = SDL_GetWindowSurface(m_window);
			if (m_windowSurface == nullptr)
			{
				success = false;
				printf("Failed to get the window surface.", SDL_GetError());
			}
			else
			{
				//Create the renderer
				m_renderer = SDL_CreateRenderer(m_window, -1, SDL_RENDERER_ACCELERATED);
				if (m_renderer == nullptr)
				{
					success = false;
					printf("Failed to create the renderer.", SDL_GetError());
				}
			}
		}
	}
	return success;
}

void Display::render(Media & media, Player & player, std::vector<Enemy>& enemies, std::vector<Laser>& playerLasers, std::vector<Laser>& enemyLasers)
{
	SDL_RenderClear(m_renderer);
	SDL_SetRenderDrawColor(m_renderer, 255, 255, 255, 0);

	//Render player
	SDL_RenderCopy(m_renderer, media.getPlayerTexture(), nullptr, &player.getPosition());

	//Render enemies
	for (auto &i : enemies)
	{
		SDL_RenderCopy(m_renderer, media.getEnemyTexture(), nullptr, &i.m_pos);
	}

	//Render Player Lasers
	for (auto &i : playerLasers)
	{
		SDL_RenderCopy(m_renderer, media.getLaserTexture(), nullptr, &i.m_pos);
	}

	for (auto &i : enemyLasers)
	{
		SDL_RenderCopy(m_renderer, media.getLaserTexture(), nullptr, &i.m_pos);
	}

	SDL_RenderPresent(m_renderer);
}

