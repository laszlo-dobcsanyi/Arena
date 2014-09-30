#ifndef Game_H
#define Game_H

#include <boost\shared_ptr.hpp>

#include "TreeLockable.hpp"
#include "Object.h"

class Game
{
public:
	TreeLockable< boost::shared_ptr< Object > > objects;

	Game();
	~Game();

	void Update(const float& _elapsed_time);

private:
	Game(const Game& _other);
	Game& operator=(const Game&_other);
};
#endif