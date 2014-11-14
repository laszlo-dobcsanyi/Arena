#ifndef GAME_HERO_H
#define GAME_HERO_H

#include <cstdint>

#include <boost\atomic.hpp>
#include <boost\shared_ptr.hpp>

#include "Game\Object.h"

struct Hero_Movement
{
public:
	enum Hero_Movement_Enum
	{
		RIGHT	= 1 << 1,
		UP		= 1 << 2,
		LEFT	= 1 << 3,
		DOWN	= 1 << 4,
		JUMP	= 1 << 5
	};

private:
	Hero_Movement();
};

class Wall;

class Hero : public Object
{
public:
	boost::shared_ptr< Wall > base = 0;
	Collision_Type base_type = Collision_Type::NONE;

	Hero(const Vector2& _center, const GLchar* _texturePath);
	~Hero();

	uint8_t movement;
	void Move(const uint8_t &_state);
	void Update(const float& _elapsed_time);

	boost::atomic< bool > disposed;
	void Dispose();

	void Collision_Hero(boost::shared_ptr< Hero > _other, const Collision_Type& _type);
	void Collision_Wall(boost::shared_ptr< Wall > _wall, const Collision_Type& _type);

private:
	Hero(const Hero& _other);
	Hero& operator=(const Hero& _other);
};
#endif