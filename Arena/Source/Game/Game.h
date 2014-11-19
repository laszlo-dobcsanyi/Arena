#ifndef GAME_GAME_H
#define GAME_GAME_H

#include <boost\atomic.hpp>
#include <boost\thread.hpp>

#include "Graphics\Renderer_Game.h"

class Arena;

class Game : public Renderer_Game
{
public:
	Arena *arena = 0;

	virtual void Dispose();

protected:
	boost::atomic< bool > disposed;

	Game();
	virtual ~Game();

	boost::thread updater;
	void Start();

	void Process();
	virtual void Update(const float &_elapsed_time) = 0;

private:
	Game(const Game& _other);
	Game& operator=(const Game&_other);
};
#endif