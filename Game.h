#pragma once
#include <SDL.h>
#include <vector>

struct Laser;
struct Enemy;
class Player;
class Media;
class Display;
class Game
{
public:
	Game();
	~Game();

	void start(Display& display, Media& media, Player& player);

private:
	bool m_quit = false;
	void addEnemy(std::vector<Enemy>& enemies);
	void moveEnemies(std::vector<Enemy>& enemies);
	void moveLasers(std::vector<Laser>& playerLasers, std::vector<Laser>& enemyLasers);

	void checkCollisions(Player& player, std::vector<Enemy>& enemies, std::vector<Laser>& playerLasers, std::vector<Laser>& enemyLasers);
	bool findPlayerLaserCollision(Laser& laser, Enemy& enemy);
	bool findEnemyLaserCollisions(Laser& laser, Player& player);
	bool checkGameOver(std::vector<Enemy>& enemies);
	void enemyShoot(std::vector<Enemy>& enemies, std::vector<Laser>& enemyLasers);
	void resetPlayerPos(Player& player);

};

