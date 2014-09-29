#ifndef ARENA_H
#define ARENA_H

#include <boost\shared_ptr.hpp>

#include "Hero.h"
#include "Wall.h"
#include "ListProcessable.hpp"

class Arena //: listProcessable_Callback< boost::shared_ptr< Hero> >
{
public:
	ListProcessable< boost::shared_ptr< Hero > > heroes;
	ListLockable< boost::shared_ptr < Wall > > walls;

	Arena();
	~Arena();

	void Update(const float& _elapsed_time);

private:
	Arena(const Arena& _other);
	Arena& operator=(const Arena&_other);
};
#endif