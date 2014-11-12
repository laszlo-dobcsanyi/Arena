#include "Game\Game.h"

#include "Macro"
#include "Game\Hero.h"
#include "Game\Wall.h"
#include "Game\Arena.h"

Game * Game::game = 0;

///
Game::Game(const Game_Type::Type &_type)
	: arena(new Arena(12)) // "Maps\\level0.data"
{
	#ifdef LOGGING
	Logger::Write(LogMask::constructor, LogObject::game, "+> Creating Game..");
	#endif
}

Game::~Game()
{
	#ifdef LOGGING
	Logger::Write(LogMask::destructor, LogObject::game, "<- Destroying Game..");
	#endif
}

///
void Game::Update(const float& _elapsed_time)
{
	arena->Update(_elapsed_time);
}
