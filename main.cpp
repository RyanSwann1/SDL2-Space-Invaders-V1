#include "Display.h"
#include "Game.h"
#include "Media.h"
#include "Player.h"

#include <SDL.h>
#include <iostream>

int main(int argc, char* args[])
{
	Display display;
	Game game;
	Media media;
	Player player;
	
	
	game.start(display, media, player);

	printf("\n\n\nYou Win!");
	SDL_Delay(3000);

	return 0;
}
