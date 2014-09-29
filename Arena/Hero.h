#ifndef HERO_H
#define HERO_H

#include "Object.h"

#include <boost\shared_ptr.hpp>

class Wall;

class Hero : public Object
{
public:
	Hero(const Vector2& _center);
	~Hero();

	void Update(const float& _elapsed_time);
	void Report();

	void Collision_Hero(boost::shared_ptr< Hero > _other, const Collision_Type& _type);
	void Collision_Wall(boost::shared_ptr< Wall > _other, const Collision_Type& _type);

private:
	Hero(const Hero& _other);
	Hero& operator=(const Hero& _other);
};
#endif