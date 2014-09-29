#ifndef WALL_H
#define WALL_H

#include "Object.h"

#include <boost\shared_ptr.hpp>

class Hero;

class Wall : public Object
{
public:
	Wall(const Vector2& _p1, const Vector2& _p2);
	Wall(const float& _x1, const float& _y1, const float& _x2, const float& _y2);
	~Wall();

	void Update(const float& _elapsed_time);
	void Report();

	void Collision_Hero(boost::shared_ptr< Hero > _other, const Collision_Type& _type);
	void Collision_Wall(boost::shared_ptr< Wall > _other, const Collision_Type& _type);

private:
	Wall(const Wall& _other);
	Wall& operator=(const Wall& _other);
};
#endif