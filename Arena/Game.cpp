#include "Game.h"

#include "Hero.h"
#include "Wall.h"
#include "Arena.h"

Game::Game() : arena("tmp.map")
{

}

Game::~Game()
{

}

//

void Game::Update(const float& _elapsed_time)
{
	arena.Update(_elapsed_time);
}
