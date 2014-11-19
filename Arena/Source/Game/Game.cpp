#include "Macro"

#include <assert.h>

#include <boost\bind.hpp>

#include "Core\Configuration.h"
#include "Game\Game.h"
#include "Game\Hero.h"
#include "Game\Wall.h"
#include "Game\Arena.h"

Game::Game() :
	disposed(false)
{
	#ifdef LOGGING
	Logger::Write(LogMask::constructor, LogObject::game, "\t+> Creating Game..");
	#endif

	arena = new Arena("Maps\\level0.data");  // 12
	updater = boost::thread(boost::bind(&Game::Process, this));

	#ifdef LOGGING
	Logger::Write(LogMask::constructor, LogObject::game, "\t<+ Game Created!");
	#endif
}

Game::~Game()
{
	#ifdef LOGGING
	Logger::Write(LogMask::destructor, LogObject::game, "\t-> Destroying Game..");
	#endif

	delete arena;

	#ifdef LOGGING
	Logger::Write(LogMask::destructor, LogObject::game, "\t<- Game Destroyed!");
	#endif
}

void Game::Dispose()
{
	#ifdef LOGGING
	Logger::Write(LogMask::destructor, LogObject::game, "\t-> Disposing Game..");
	#endif

	if (!disposed) disposed = true;
	updater.interrupt();
	updater.join();

	//

	delete this;

	#ifdef LOGGING
	Logger::Write(LogMask::destructor, LogObject::game, "\t<- Game Disposed!");
	#endif
}

void Game::Process()
{
	float update_interval = Configuration::game_update_interval;

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
