#ifndef GAME_GAME_H
#define GAME_GAME_H

#include <assert.h>

#include <boost\atomic.hpp>
#include <boost\thread.hpp>

class Arena;

class Game_Type
{
public:
	enum Type
	{
		LOCAL,
		NETWORK
	};

private:
	Game_Type();
};

class Game
{
public:
	Arena *arena = 0;

	static Game * Create(const Game_Type::Type &_type) { assert(!game); game = new Game(_type); return game; }
	static Game * Get() { assert(game);  return game; }
	static void Destroy() { delete game; game = 0; }

private:
	static Game *game;

	boost::atomic< bool > disposed;
	boost::thread updater;

	Game(const Game_Type::Type &_type);
	~Game();

	void Update();

	Game(const Game& _other);
	Game& operator=(const Game&_other);
};
#endif