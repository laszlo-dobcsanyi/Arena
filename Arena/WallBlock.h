#ifndef WALL_BLOCK_H
#define WALL_BLOCK_H

#include <forward_list>
#include <boost\shared_ptr.hpp>

#include "Object.h"

class Wall;

class WallBlock : public Object
{
public:
	std::forward_list< boost::shared_ptr< Wall > > walls;

	WallBlock() : Object(Vector2(0., 0.), 0., 0.) { }
	~WallBlock() { }

	void Add(boost::shared_ptr< Wall > _wall);
	void Finalize();

private:
	WallBlock(const WallBlock& _other);
	WallBlock& operator=(const WallBlock& _other);
};
#endif