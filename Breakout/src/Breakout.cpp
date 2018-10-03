#include "Game.h"

#include <SDL.h> 

int main(int argc, char* args[]) 
{
	Game *game = new Game();
	game->start();

	return 0;
}