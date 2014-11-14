#include "Macro"

#include "Game\Game.h"
#include "Game\Arena.h"

Game_Local::Game_Local()
{

}

Game_Local::~Game_Local()
{

}

void Game_Local::Update(const float &_elapsed_time)
{
	arena->Update(_elapsed_time);
}
