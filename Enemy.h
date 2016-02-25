#pragma once

#include <SDL.h>
#include "MoveDirection.h"

struct Enemy
{
	Enemy(SDL_Rect pos, int movementSpeed, MoveDirection dir)
	{
		m_pos = pos;
		m_movementSpeed = movementSpeed;
		m_dir = dir;
	}

	SDL_Rect m_pos; //Position of enemy
	int m_movementSpeed = 0; //Movement speed of enemy
	MoveDirection m_dir; //Movement direction of enemy
	int MIN_X_POS = 0;
	int MAX_X_POS = 750;
};

