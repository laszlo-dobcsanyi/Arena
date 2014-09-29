#include "Wall.h"

#include <iostream>

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

//

void Wall::Update(const float& _elapsed_time)
{
	//Object::Update(_elapsed_time);
}

void Wall::Report()
{
	std::cout << "Wall @ " << center.x << ":" << center.y << std::endl;
}

///

void Wall::Collision_Hero(boost::shared_ptr< Hero > _other, const Collision_Type& _type)
{

}

void Wall::Collision_Wall(boost::shared_ptr< Wall > _other, const Collision_Type& _type)
{

}
