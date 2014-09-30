#ifndef Game_H
#define Game_H

#include "Arena.h"

class Game
{
public:
	Arena arena;

	Game();
	~Game();

	void Update(const float& _elapsed_time);

private:
	Game(const Game& _other);
	Game& operator=(const Game&_other);
};
#endif