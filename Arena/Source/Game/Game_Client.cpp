#include "Macro"

#include "Game\Game.h"
#include "Game\Arena.h"

Game_Client::Game_Client()
{

}

Game_Client::~Game_Client()
{

}

void Game_Client::Update(const float &_elapsed_time)
{
	arena->Update(_elapsed_time);
}