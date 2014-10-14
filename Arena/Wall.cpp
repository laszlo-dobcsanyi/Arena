#include "Wall.h"

#include <iostream>

#include <boost\random.hpp>

#include "Hero.h"

Wall::Wall(const Vector2& _p1, const Vector2& _p2, const GLchar* _texturePath)
	: Wall(_p1.x, _p1.y, _p2.x, _p2.y, _texturePath)
{

}

Wall::Wall(const Vector2 &_center, const float &_width, const float &_height, const GLchar* _texturePath)
	: Object(_center, _width, _height, _texturePath)
{

}


Wall::Wall(const float& _x1, const float& _y1, const float& _x2, const float& _y2, const GLchar* _texturePath)
	: Object(Vector2((_x1 + _x2) / 2, (_y1 + _y2) / 2), (_x2 - _x1) / 2, (_y1 - _y2) / 2, _texturePath)
{

}

Wall::~Wall()
{

}

///

boost::mt19937 rng;
float float_rng(float min, float max)
{
	boost::uniform_real<float> u(min, max);
	boost::variate_generator<boost::mt19937&, boost::uniform_real<float> > gen(rng, u);
	return gen();
}

void Wall::Collision_Hero(boost::shared_ptr< Hero > _hero, const Collision_Type& _type)
{
	switch (_type)
	{
		case Collision_Type::RIGHT:		_hero->updated_center.x = center.x + width + _hero->width;		_hero->velocity.x = 0.;	break;
		case Collision_Type::TOP:		_hero->updated_center.y = center.y + height + _hero->height;	_hero->velocity.y = 0.; break;
		case Collision_Type::LEFT:		_hero->updated_center.x = center.x - width - _hero->width;		_hero->velocity.x = 0.;	break;
		case Collision_Type::BOTTOM:	_hero->updated_center.y = center.y - height - _hero->height;	_hero->velocity.y = 0.; break;
		default:						std::cout << "# Collision failed!" << std::endl;
	}

	_hero->force = Vector2(float_rng(-5., 5.), float_rng(-5., 5.));
}
