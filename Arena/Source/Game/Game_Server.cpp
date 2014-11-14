#include "Macro"

#include "Game\Game.h"
#include "Game\Arena.h"

Game_Server::Game_Server()
{

}

Game_Server::~Game_Server()
{

}

void Game_Server::Update(const float &_elapsed_time)
{
	arena->Update(_elapsed_time);

}