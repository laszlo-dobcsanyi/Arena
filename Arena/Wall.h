#ifndef WALL_H
#define WALL_H

#include <forward_list>

#include <boost\shared_ptr.hpp>

#include "Object.h"

class Hero;

class Wall : public Object
{
public:
	std::forward_list< boost::shared_ptr< Hero > > heroes;

	Wall(const Vector2& _p1, const Vector2& _p2);
	Wall(const float& _x1, const float& _y1, const float& _x2, const float& _y2);
	~Wall();

	void Collision_Hero(boost::shared_ptr< Hero > _hero, const Collision_Type& _type);

private:
	Wall(const Wall& _other);
	Wall& operator=(const Wall& _other);
};
#endif