#ifndef Game_H
#define Game_H

#include <boost\shared_ptr.hpp>

#include "Hero.h"
#include "Wall.h"
#include "ListProcessable.hpp"
#include "TreeLockable.hpp"

class Game //: listProcessable_Callback< boost::shared_ptr< Hero> >
{
public:
	ListProcessable< boost::shared_ptr< Hero > > heroes;
	ListLockable< boost::shared_ptr < Wall > > walls;

	TreeLockable< Object > objects;

	Game();
	~Game();

	void Update(const float& _elapsed_time);

private:
	Game(const Game& _other);
	Game& operator=(const Game&_other);
};
#endif