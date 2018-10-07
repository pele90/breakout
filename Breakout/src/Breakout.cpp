#include <SDL.h>

#include "Game.h"
#include <vld.h> // Visual Leak Detector lib for hunting memory leaks

int main(int argc, char* args[]) 
{
	Game game = Game();
	game.run();

	return 0;
}