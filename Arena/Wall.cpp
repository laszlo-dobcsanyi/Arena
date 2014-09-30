#include "Wall.h"

#include <iostream>

#include "Hero.h"

Wall::Wall(const Vector2& _p1, const Vector2& _p2)
	: Wall(_p1.x, _p1.y, _p2.x, _p2.y)
{

}

Wall::Wall(const float& _x1, const float& _y1, const float& _x2, const float& _y2)
	: Object(Vector2((_x1 + _x2) / 2, (_y1 + _y2) / 2), (_x2 - _x1) / 2, (_y1 - _y2) / 2)
{

}

Wall::~Wall()
{

}

///

void Wall::Collision_Hero(boost::shared_ptr< Hero > _hero, const Collision_Type& _type)
{
	switch (_type)
	{
		case Collision_Type::RIGHT:		_hero->updated_center.x = center.x + width	+ _hero->width;		break;
		case Collision_Type::TOP:		_hero->updated_center.y = center.y + height	+ _hero->height;	break;
		case Collision_Type::LEFT:		_hero->updated_center.x = center.x - width	- _hero->width;		break;
		case Collision_Type::BOTTOM:	_hero->updated_center.y = center.y - height	- _hero->height;	break;
		default:						std::cout << "# Collision failed!" << std::endl;
	}
}
