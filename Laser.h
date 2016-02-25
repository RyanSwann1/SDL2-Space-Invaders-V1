#pragma once
#include <SDL.h>
#include "MoveDirection.h"
struct Laser
{
	Laser(SDL_Rect pos, int movementSpeed, MoveDirection dir)
	{
		m_pos = pos;
		m_movementSpeed = movementSpeed;
		m_dir = dir;
	}

	SDL_Rect m_pos; //Position of enemy
	int m_movementSpeed = 0; //Movement speed of enemy
	MoveDirection m_dir; //Movement direction of enemy
};
