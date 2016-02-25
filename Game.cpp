#include "Game.h"
#include "Display.h"
#include "Media.h"
#include "Player.h"
#include "Enemy.h"
#include "MoveDirection.h"
#include "Laser.h"

#include <iostream>

Game::Game()
{
}

Game::~Game()
{
}

void Game::start(Display& display, Media& media, Player& player)
{
	//Initialize SDL
	if (!display.init())
	{
		printf("Failed to initailize.", SDL_GetError());
	}
	else
	{
		//Load all media
		if (!media.load(display))
		{
			printf("Failed to load media", SDL_GetError());
		}
		else
		{
			SDL_Event e; 
			
			std::vector<Enemy> enemies; //Holds all enemies
			std::vector<Laser> playerLasers; //Holds all of player lasers
			std::vector<Laser> enemyLasers;

			addEnemy(enemies); //Adds enemies to the game
			//Begin game loop
			while (!m_quit)
			{
				//Event management
				while (SDL_PollEvent(&e) != 0)
				{
					if(e.type == SDL_KEYDOWN)
					{ 
						player.movement(e);
					}
					if (e.type == SDL_MOUSEBUTTONDOWN)
					{
						player.shoot(playerLasers);
					}
				}

				//Shoot
				enemyShoot(enemies, enemyLasers);

				//Movement
				player.movementBounds();
				moveLasers(playerLasers, enemyLasers);
				moveEnemies(enemies);

				//Collision detection
				checkCollisions(player, enemies, playerLasers, enemyLasers);
				
				//Check game over

				m_quit = checkGameOver(enemies);
				//Render
				display.render(media, player, enemies, playerLasers, enemyLasers);



				//Simulate 60 fps - Read on tutorial, not entirely sure if this is ok. 
				SDL_Delay(16);
			}
		}
	}
}

void Game::addEnemy(std::vector<Enemy>& enemies)
{
	int spawnXPos = 100;
	int newSpawnXPos = 100; 
	int spawnYPos = 100;
	int enemyWidth = 50;
	int enemyHeight = 50;
	int numbOfEnemies = 18;
	int movementSpeed = 3;

	for (int i = 0; i < numbOfEnemies; i++)
	{
		enemies.push_back(Enemy({ spawnXPos, spawnYPos, enemyWidth, enemyHeight }, movementSpeed, MoveDirection::LEFT));
		spawnXPos += newSpawnXPos; //Spawns enemies along a rowd
		//Make new row
		if (spawnXPos == 700) {
			spawnXPos = 100;
			spawnYPos += 75;
		}
	}
}

void Game::moveEnemies(std::vector<Enemy>& enemies)
{
	int newYPos = 20; //Move enemies down everytime they hit a wall
	for (auto &enemy : enemies)
	{
		//Move Left
		if (enemy.m_dir == MoveDirection::LEFT)
		{
			enemy.m_pos.x -= enemy.m_movementSpeed;
			//If an enemy has exceeded allowed bounds, change direction
			if (enemy.m_pos.x < enemy.MIN_X_POS)
			{
				for (auto &i : enemies)
				{
					i.m_dir = MoveDirection::RIGHT;
					i.m_pos.y += newYPos;
				}

			}
		}
		//Move Right
		if (enemy.m_dir == MoveDirection::RIGHT)
		{
			enemy.m_pos.x += enemy.m_movementSpeed;
			//If enemy exceeds allowed bounds, change direction
			if (enemy.m_pos.x > enemy.MAX_X_POS)
			{
				for(auto &i : enemies)
				{ 
					i.m_dir = MoveDirection::LEFT;
					i.m_pos.y += newYPos;
				}
			}
		}
	}
}

void Game::moveLasers(std::vector<Laser>& playerLasers, std::vector<Laser>& enemyLasers)
{
	//Movement of player lasers
	for (auto &playerLaser : playerLasers)
	{
		if (playerLaser.m_dir == MoveDirection::UP)
		{
			playerLaser.m_pos.y -= playerLaser.m_movementSpeed;
		}
	}
	//Movement of enemy lasers
	for (auto &enemyLaser : enemyLasers)
	{
		if (enemyLaser.m_dir == MoveDirection::DOWN)
		{
			enemyLaser.m_pos.y += enemyLaser.m_movementSpeed;
		}
	}
}

void Game::checkCollisions(Player& player, std::vector<Enemy>& enemies, std::vector<Laser>& playerLasers, std::vector<Laser>& enemyLasers)
{
	//checkCollisions(player, enemies, playerLasers, enemyLasers);
	//Check for playerLaser/Enemy collision
	for (int playerLaser = 0; playerLaser < playerLasers.size(); playerLaser++)
	{
		for (int enemy = 0; enemy < enemies.size(); enemy++)
		{
			//If collision has been detected, delete both playerLaser and Enemy
			if (findPlayerLaserCollision(playerLasers[playerLaser], enemies[enemy]))
			{
				printf("Collision");
				playerLasers.erase(playerLasers.begin() + playerLaser);
				enemies.erase(enemies.begin() + enemy);
				
				return;
			}
		}
	}
	for (int enemyLaser = 0; enemyLaser < enemyLasers.size(); enemyLaser++)
	{
		if (findEnemyLaserCollisions(enemyLasers[enemyLaser], player))
		{
			printf("Player collision");
			enemyLasers.erase(enemyLasers.begin() + enemyLaser);
			resetPlayerPos(player);
			return;
		}
	}
	
	//No collisions detected
}

bool Game::findPlayerLaserCollision(Laser& playerLaser, Enemy& enemy)
{
	//Player laser collisions
	int playerLaserLeft = playerLaser.m_pos.x;
	int playerLaserRight = playerLaser.m_pos.x + playerLaser.m_pos.w;
	int playerLaserTop = playerLaser.m_pos.y;
	int playerLaserBot = playerLaser.m_pos.y + playerLaser.m_pos.h;

	//Enemy collisions
	int enemyLeft = enemy.m_pos.x;
	int enemyRight = enemy.m_pos.x + enemy.m_pos.w;
	int enemyTop = enemy.m_pos.y;
	int enemyBot = enemy.m_pos.y + enemy.m_pos.h;

	//Check for collisions
	if (playerLaserRight < enemyLeft) {
		return false;
	}
	if (playerLaserLeft > enemyRight) {
		return false;
	}
	if (playerLaserTop > enemyBot) {
		return false;
	}
	if (playerLaserBot < enemyTop) {
		return false;
	}

	//If collision
	return true;
}

bool Game::findEnemyLaserCollisions(Laser & laser, Player & player)
{

	//Player Collisions
	int playerLeft = player.getPositionX();
	int playerRight = player.getPositionX() + player.getWidth();
	int playerTop = player.getPositionY();
	int playerBot = player.getPositionY() + player.getHeight();
		
	//EnemyLaser Collision
	int laserLeft = laser.m_pos.x;
	int laserRight = laser.m_pos.x + laser.m_pos.w;
	int laserTop = laser.m_pos.y;
	int laserBot = laser.m_pos.y + laser.m_pos.h;

	//Detect collisions
	if (playerLeft > laserRight) {
		return false;
	}
	if (playerRight < laserLeft) {
		return false;
	}
	if (playerTop > laserBot) {
		return false;
	}
	if (playerBot < laserTop) {
		return false;
	}
	//Collision
	return true;
}



bool Game::checkGameOver(std::vector<Enemy>& enemies)
{
	if (enemies.size() == 0)
	{
		printf("Game Over!");
		return true;
	}
	return false;
}

void Game::enemyShoot(std::vector<Enemy>& enemies, std::vector<Laser>& enemyLasers)
{
	//If any enemies are alive.
	if (enemies.size() > 0)
	{
		Uint32 startTime = SDL_GetTicks();
		int randEnemy = rand() % enemies.size();

		//Starting position of laser
		int startXPos = enemies[randEnemy].m_pos.x;
		int startYPos = enemies[randEnemy].m_pos.y;
		//Size of laser
		int sizeWidth = 25;
		int sizeHeight = 50;
		//Movement speed of laser
		int movementSpeed = 8;
		//Direction of laser
		MoveDirection dir = MoveDirection::DOWN;

		if (startTime % 125 == 0)
		{
			enemyLasers.push_back(Laser({ startXPos, startYPos, sizeWidth, sizeHeight }, movementSpeed, dir));
		}
	}
}

void Game::resetPlayerPos(Player& player)
{
	player.setXPos(350);
	player.setYPos(700);
}
