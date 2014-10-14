#ifndef HERO_H
#define HERO_H

#include "Object.h"

#include <boost\shared_ptr.hpp>

class Wall;

class Hero : public Object
{
public:
	boost::shared_ptr< Wall > base = 0;
	Collision_Type base_type = Collision_Type::NONE;

	Hero(const Vector2& _center, const GLchar* _texturePath);
	~Hero();

	void Update(const float& _elapsed_time);
	void Report();

	void Collision_Hero(boost::shared_ptr< Hero > _other, const Collision_Type& _type);
	void Collision_Wall(boost::shared_ptr< Wall > _wall, const Collision_Type& _type);

private:
	Hero(const Hero& _other);
	Hero& operator=(const Hero& _other);
};
#endif