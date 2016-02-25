#pragma once

#include <SDL.h>
#include <vector>

struct Enemy;
struct Laser;
class Player
{
public:
	Player();
	~Player();
	void movement(SDL_Event& e);
	void movementBounds();
	void init(); //Initialize

	SDL_Rect getPosition() { return m_pos; }
	int getPositionY() { return m_pos.y; }
	int getPositionX() { return m_pos.x; }
	int getWidth() { return SIZE_WIDTH; }
	int getHeight() { return SIZE_HEIGHT; }
	void setYPos(int yPos) { m_pos.y = yPos; }
	void setXPos(int xPos) { m_pos.x = xPos; }

	void shoot(std::vector<Laser>& playerLasers);

private:
	//position of player
	SDL_Rect m_pos;
	//Size of player
	const int SIZE_WIDTH = 50;
	const int SIZE_HEIGHT = 50;
	//Starting position of player
	const int START_XPOS = 350;
	const int START_YPOS = 700;
	//Movement speed of player
	const int MOVEMENT_SPEED = 10;
	//MovementBoundaries
	const int xMinDistance = 0;
	const int xMaxDistance = 775;

};
