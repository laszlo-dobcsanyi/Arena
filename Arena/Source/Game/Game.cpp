#include "Macro"

#include <assert.h>

#include <boost\bind.hpp>

#include "Core\Configuration.h"
#include "Game\Game.h"
#include "Game\Hero.h"
#include "Game\Wall.h"
#include "Game\Arena.h"

Game * Game::game = 0;

Game * Game::Create(const Game_Type::Type &_type)
{
	assert(!game);
	switch (_type)
	{
		case Game_Type::LOCAL:	game = new Game_Local(); break;
		case Game_Type::SERVER:	game = new Game_Server(); break;
		case Game_Type::CLIENT:	game = new Game_Client(); break;
	}
	assert(game);
	return game;
}

Game * Game::Get()
{ 
	return game;
}

void Game::Destroy()
{
	delete game;
	game = 0;
}

///

Game::Game() :
	arena(new Arena("Maps\\level0.data")), // 12
	disposed(false),
	updater(boost::bind(&Game::Process, this))
{
	#ifdef LOGGING
	Logger::Write(LogMask::constructor, LogObject::game, "<+ Game Created!");
	#endif
}

Game::~Game()
{
	#ifdef LOGGING
	Logger::Write(LogMask::destructor, LogObject::game, "-> Destroying Game..");
	#endif

	if (!disposed) disposed = true;
	updater.join();

	delete arena;

	#ifdef LOGGING
	Logger::Write(LogMask::destructor, LogObject::game, "<- Game Destroyed!");
	#endif
}

void Game::Process()
{
	float update_interval = Configuration::Get()->game_update_interval;

	float elapsed_time = 0.;
	boost::chrono::steady_clock::time_point last_time = boost::chrono::steady_clock::now();
	do
	{
		boost::chrono::steady_clock::time_point now = boost::chrono::steady_clock::now();
		boost::chrono::duration<float> difference = now - last_time;
		elapsed_time += difference.count();
		last_time = now;

		// Update
		if (update_interval < elapsed_time)
		{
			Update(elapsed_time);

			elapsed_time = 0.f;
		}
	} while (!disposed);
}
