#include "Hero.h"

#include <iostream>

#include "Wall.h"

/// Constructor/Destructor
Hero::Hero(const Vector2& _center, const GLchar* _texturePath)
	: Object(_center, 32, 32, _texturePath)
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
		/*// Free fall
		case Collision_Type::NONE:
			velocity = velocity + (Vector2(-2., -1.) * _elapsed_time);
			break;

		case Collision_Type::RIGHT:
			velocity = velocity + (Vector2(0., -1.) * _elapsed_time * 0.5);
			break;

		case Collision_Type::TOP:
			velocity = Vector2(0., 0.);
			break;

		case Collision_Type::LEFT:
			velocity = velocity + (Vector2(0., -1.) * _elapsed_time * 0.5);
			break;

		case Collision_Type::BOTTOM:
			velocity = velocity + (Vector2(0., -1.) * _elapsed_time);
			break;*/

		default:
			velocity = velocity + (force * _elapsed_time);
			break;
	}

	updated_center = center + velocity;
}

void Hero::Report()
{
	std::cout << "Hero C [" << center.x << ":" << center.y << "] V [" << velocity.x << ":" << velocity.y << "]" << std::endl;
}

///

void Hero::Collision_Hero(boost::shared_ptr< Hero > _other, const Collision_Type& _type)
{

}

void Hero::Collision_Wall(boost::shared_ptr< Wall > _wall, const Collision_Type& _type)
{
	if (base)
	{
		if (_type < base_type)
		{
			base = _wall;
			base_type = _type;
		}
	}
	else
	{
		//if (base_type != Collision_Type::BOTTOM)
		{
			base = _wall;
			base_type = _type;
		}
	}

	std::cout << "Hero COLLISION: " << _type << " : C [" << updated_center.x << ":" << updated_center.y << "] V [" << velocity.x << ":" << velocity.y << "]" << std::endl;
}
