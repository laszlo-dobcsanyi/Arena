#include "Game.h"

#include "Hero.h"
#include "Wall.h"
#include "Arena.h"

Game * Game::game = 0;

///
Game::Game(const Game_Type::Type &_type)
	: arena(new Arena("level1.lvl"))
{

}

Game::~Game()
{

}

///
void Game::Update(const float& _elapsed_time)
{
	arena->Update(_elapsed_time);
}
