#ifndef GAME_GAME_LOCAL_H
#define GAME_GAME_LOCAL_H

#include "Game\Game.h"
#include "Graphics\Renderer_Game.h"

class Game_Local : public Game
{
public:
	Game_Local();
	virtual ~Game_Local();

	void Update(const float &_elapsed_time);

private:
	Game_Local(const Game_Local &_other);
	Game_Local & operator=(const Game_Local &_other);
};
#endif