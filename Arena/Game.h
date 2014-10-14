#ifndef Game_H
#define Game_H

#include <assert.h>

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
	static Game * Get() { assert(game); return game; }
	static void Destroy() { delete game; game = 0; }

	void Update(const float& _elapsed_time);

private:
	static Game *game;

	Game(const Game_Type::Type &_type);
	~Game();

	Game(const Game& _other);
	Game& operator=(const Game&_other);
};
#endif