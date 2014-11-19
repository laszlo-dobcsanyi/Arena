#include "Macro"

#include "Core\Configuration.h"
#include "Game\Arena.h"
#include "Game\Game_Server.h"

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