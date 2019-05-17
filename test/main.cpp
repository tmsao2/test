#include <DxLib.h>
#include <iostream>
#include "Game.h"


int main() 
{
	Game& game = Game::Instance();
	game.Initialize();
	game.Run();
	game.Terminate();
}