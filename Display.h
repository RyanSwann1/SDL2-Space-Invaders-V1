#pragma once
#include <SDL.h>
#include <vector>
struct Laser;
struct Enemy;
class Player;
class Media;
class Display
{
public:
	Display();
	~Display();

	bool init();
	void render(Media& media, Player& player, std::vector<Enemy>& enemies, std::vector<Laser>& playerLasers, std::vector<Laser>& enemyLasers);

	SDL_Surface* getWindowSurface() { return m_windowSurface; }
	SDL_Renderer* getRenderer() { return m_renderer; }
protected:


private:
	SDL_Window* m_window = nullptr;
	SDL_Surface* m_windowSurface = nullptr;
	SDL_Renderer* m_renderer = nullptr;

	//Screen resolution
	const int SCREEN_WIDTH = 800;
	const int SCREEN_HEIGHT = 800;

	
};

