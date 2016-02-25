#include "Player.h"
#include "Laser.h"


Player::Player()
{
	init();
}

Player::~Player()
{
}

void Player::movement(SDL_Event& e)
{
	switch (e.key.keysym.sym)
	{
		//Move right
	case SDLK_d: m_pos.x += MOVEMENT_SPEED;
		break;
		//Move left
	case SDLK_a: m_pos.x -= MOVEMENT_SPEED;
		break;
	
	}
}

void Player::movementBounds()
{
	if (m_pos.x <= xMinDistance) {
		m_pos.x = xMinDistance;
	}
	if (m_pos.x >= xMaxDistance) {
		m_pos.x = xMaxDistance;
	}
}

void Player::init()
{
	//Size of player
	m_pos.h = SIZE_HEIGHT;
	m_pos.w = SIZE_WIDTH;
	//starting position
	m_pos.x = START_XPOS;
	m_pos.y = START_YPOS;
}

void Player::shoot(std::vector<Laser>& playerLasers)
{
	int startXPos = m_pos.x + 10;
	int startYPos = m_pos.y - 35;
	int movementSpeed = 8;
	int sizeWidth = 25;
	int sizeHeight = 50;
	MoveDirection dir = MoveDirection::UP;

	playerLasers.push_back(Laser({ startXPos, startYPos, sizeWidth, sizeHeight }, movementSpeed, dir));
}
