#include "Macro"

#include "Game\Arena.h"
#include "Game\Game_Local.h"

Game_Local::Game_Local() :
	Renderer_Game(this)
{

}

Game_Local::~Game_Local()
{
	#ifdef LOGGING
	Logger::Write(LogMask::destructor, LogObject::game, "-> Destroying Local Game..");
	#endif

	#ifdef LOGGING
	Logger::Write(LogMask::destructor, LogObject::game, "<- Local Game Destroyed!");
	#endif
}

void Game_Local::Update(const float &_elapsed_time)
{
	arena->Update(_elapsed_time);
}
