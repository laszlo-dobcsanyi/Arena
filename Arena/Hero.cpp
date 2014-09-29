#include "Hero.h"

#include <iostream>

#include "Wall.h"

/// Constructor/Destructor
Hero::Hero(const Vector2& _center)
	: Object(_center, 32, 32)
{

}

Hero::~Hero()
{

}

///

void Hero::Update(const float& _elapsed_time)
{
	switch (base_type)
	{
		// Free fall
		case Collision_Type::NONE:
			velocity = velocity + (Vector2(-1., +1.) * _elapsed_time);
			break;

		case Collision_Type::RIGHT:
			velocity = base->velocity;
			break;

		case Collision_Type::TOP:
			velocity = base->velocity;
			break;

		case Collision_Type::LEFT:
			velocity = base->velocity;
			break;

		case Collision_Type::BOTTOM:
			velocity = base->velocity;
			break;
	}

	Object::Update(_elapsed_time);
}

void Hero::Report()
{
	std::cout << "Hero C [" << center.x << ":" << center.y << "] V [" << velocity.x << ":" << velocity.y << "]" << std::endl;
}

///

void Hero::Collision_Hero(boost::shared_ptr< Hero > _other, const Collision_Type& _type)
{

}

void Hero::Collision_Wall(boost::shared_ptr< Wall > _other, const Collision_Type& _type)
{
	base = _other;
	base_type = _type;

	//velocity = Vector2(0., 0.);
	updated_center = center;

	std::cout << "Hero COLLISION: " << _type << " : C [" << center.x << ":" << center.y << "] V [" << velocity.x << ":" << velocity.y << "]" << std::endl;
}
