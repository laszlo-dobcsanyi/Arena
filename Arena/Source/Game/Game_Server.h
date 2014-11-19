#ifndef GAME_GAME_SERVER_H
#define GAME_GAME_SERVER_H

#include "Game\Game.h"

class Game_Server : public Game
{
public:
	Game_Server();
	virtual ~Game_Server();

	void Update(const float &_elapsed_time);

private:
	Game_Server(const Game_Server &_other);
	Game_Server operator=(const Game_Server &_other);
};
#endif