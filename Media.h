#pragma once
#include <SDL.h>
#include <string>


class Display;
class Media
{
public:
	Media();
	~Media();

	bool load(Display& display);
	SDL_Texture* getPlayerTexture() { return m_player; }
	SDL_Texture* getEnemyTexture() { return m_enemy; }
	SDL_Texture* getLaserTexture() { return m_laser; }
protected:


private:
	SDL_Surface* loadSurface(Display& display, std::string path);
	SDL_Texture* loadTexture(Display& display, std::string path);

	SDL_Texture* m_laser = nullptr;
	SDL_Texture* m_player = nullptr;
	SDL_Texture* m_enemy = nullptr;


};

